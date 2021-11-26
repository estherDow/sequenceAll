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


    WiFiService() {

//TODO:PROPER ERROR HANDLING MY G
        //if(!initSTA()) {
            initAP();
        //}
        server = new AsyncWebServer(80);
        if (!MDNS.begin("sequenceall")) {
            Serial.println("Error starting mDNS");
            return;
        }
        MDNS.addService("http", "tcp", 80);

        auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_sta",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();
                if (!jsonObject.isNull() && jsonObject["ssid"]) {
                    NVSService::writeStringToNVS(
                            "STAssid",
                            jsonObject["ssid"]);
                    NVSService::writeStringToNVS(
                            "STApassword",
                            jsonObject["password"]);
                }

                NVSService::writeIntToNVS(
                        "SetSTA",
                        1);
                request->send(
                        200,
                        "application/json",
                        {}
                );
        });

        auto *handleAPRequest = new AsyncCallbackJsonWebHandler(
            "/set_ap",
           [](AsyncWebServerRequest *request,
              JsonVariant &json) {
               const JsonObject &jsonObject = json.as<JsonObject>();

               if (!jsonObject.isNull() && jsonObject["ssid"]) {
                   NVSService::writeStringToNVS(
                           "APssid",
                           jsonObject["ssid"]);
                   NVSService::writeStringToNVS(
                           "APpassword",
                           jsonObject["password"]);
               }

               NVSService::writeIntToNVS(
                       "SetAP",
                       1);
               request->send(
                       200,
                       "application/json",
                       {}
               );
       });

        server->addHandler(handleSTARequest);
        server->addHandler(handleAPRequest);
        server->begin();

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

    int oldState = 0;
    int interval = 2000;
    void handleWifiMode() {
        int currentstate = millis();
        if (currentstate > oldState + interval) {
            _doHandleWifiMode();
            oldState+=interval;
        }
    }

private:

    AsyncWebServer * server{};

    void _doSetSTA(String newSSID, String newPassword) {
        WiFi.begin((char *) newSSID.c_str(), (char *) newPassword.c_str());
        while (WiFi.status() != WL_CONNECTED) {}
        Serial.println("connected to wifi...");
        Serial.println(WiFi.localIP());
    }

    int _doSetAP(String ssid, String password) {
        WiFi.softAP((char *) ssid.c_str(), (char *) password.c_str());
        return 1;
    }

    void _doHandleWifiMode() {
        if(NVSService::readIntFromNVS("SetAP")) {
            initAP();
            NVSService::writeIntToNVS(
                    "SetAP",
                    0);
        }
        if(NVSService::readIntFromNVS("SetSTA")) {
            if(!initSTA()){
                initAP();
            }

            NVSService::writeIntToNVS(
                    "SetSTA",
                    0);
        }
    }
};


#endif
