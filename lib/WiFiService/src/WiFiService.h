#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NVSService.h>
#include <Arduino.h>
#include <macros.h>


class WiFiService {
public:

    String apSSID;
    String apPassword;

    String staSSID;
    String staPassword;

    void init() {
        AsyncWebServer server(80);
        serverPtr = &server;

        if(!initSTA()) {
            initAP();
        }

        Serial.println(WiFi.localIP());

        if (!MDNS.begin("sequenceall")) {
            Serial.println("Error starting mDNS");
            return;
        }
        MDNS.addService("http", "tcp", 80);

        AsyncCallbackJsonWebHandler *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_sta",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();
                if (jsonObject.isNull()) {
                    NVSService::writeIntToNVS(
                            "IsNewPassword",
                            0);
                }
                NVSService::writeStringToNVS(
                        "STAssid",
                        jsonObject["ssid"]);
                NVSService::writeStringToNVS(
                        "STApassword",
                        jsonObject["password"]);
                NVSService::writeIntToNVS(
                        "IsNewPassword",
                        1);
                request->send(
                        200,
                        "application/json",
                        {}
                );
        });

        AsyncCallbackJsonWebHandler *handleAPRequest = new AsyncCallbackJsonWebHandler(
            "/set_ap",
           [](AsyncWebServerRequest *request,
              JsonVariant &json) {
               const JsonObject &jsonObject = json.as<JsonObject>();

               NVSService::writeStringToNVS(
                       "APssid",
                       jsonObject["ssid"]);
               NVSService::writeStringToNVS(
                       "APpassword",
                       jsonObject["password"]);
               request->send(
                       200,
                       "application/json",
                       {}
               );
       });

        serverPtr->addHandler(handleSTARequest);
        serverPtr->addHandler(handleAPRequest);
    }

    void initAP() {
        String ssid = NVSService::readStringFromNVS("APssid");
        String password = NVSService::readStringFromNVS("APpassword");
        if (ssid.length() == 0) {
           ssid = DEFAULT_AP_SSID;
           password = DEFAULT_AP_PASSWORD;
        }
        _doSetAP(ssid, password);
    }

    bool initSTA() {
        WiFi.mode(WIFI_STA);
        uint8_t numberNetworks = WiFi.scanNetworks();
        String ssid = NVSService::readStringFromNVS("STAssid");
        String password = NVSService::readStringFromNVS("STApassword");
        if (ssid.length() == 0) {
            return 0;
        }
        for (uint8_t i = 0; i < numberNetworks; i++) {
            if (WiFi.SSID(i) == (char *) ssid.c_str()) {
                _doSetSTA(ssid, password);
                return 1;
            }
        }
        return 0;
    }

private:

    AsyncWebServer *serverPtr;

    void _doSetSTA(String newSSID, String newPassword) {
        WiFi.begin(((char *) newSSID.c_str(), (char *) newPassword.c_str()));
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
        }
        Serial.println("connected to wifi...");
        Serial.println(WiFi.localIP());
    }

    int _doSetAP(String ssid, String password) {
        WiFi.softAP((char *) ssid.c_str(), (char *) password.c_str());
        return 1;
    }
};


#endif
