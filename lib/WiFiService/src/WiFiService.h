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

        initAP();
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

                NVSService::writeStringToNVS(
                        "STAssid",
                        jsonObject["ssid"]);
                NVSService::writeStringToNVS(
                        "STApassword",
                        jsonObject["password"]);
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
        //TODO: use ternary expression
        String ssid = NVSService::readStringFromNVS("APssid");
        String password = NVSService::readStringFromNVS("APpassword");
        if (ssid.length() == 0) {
           ssid = DEFAULT_AP_SSID;
           password = DEFAULT_AP_PASSWORD;
        }
        _doSetAP(ssid, password);
    }

private:

    AsyncWebServer *serverPtr;

    int _doSetSTA(String newSSID, String newPassword) {
        WiFi.mode(WIFI_AP_STA);
        uint8_t numberNetworks = WiFi.scanNetworks();
        for (uint8_t i; i < numberNetworks; i++) {
            if (WiFi.SSID(i) == (char *) newSSID.c_str()) {
                WiFi.begin(((char *) newSSID.c_str(), (char *) newPassword.c_str()));
                while (WiFi.status() != WL_CONNECTED) {
                    Serial.print(".");
                }
                Serial.println("connected to wifi...");
                Serial.println(WiFi.localIP());
                return 1;
            }
        }
        WiFi.reconnect();
        return 0;
    }

    int _doSetAP(String ssid, String password) {
        WiFi.softAP((char *) ssid.c_str(), (char *) password.c_str());
        return 1;
    }
};


#endif
