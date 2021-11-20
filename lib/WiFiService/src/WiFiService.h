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


class WiFiService {
public:

    static const char * apSSID;
    static const char * apPassword;

    static const char * staSSID;
    static const char * staPassword;

  void init() {
    AsyncWebServer server(80);
    serverPtr = &server;

    initAP("sequenceAll", "pautsau1");
    Serial.println(WiFi.localIP());

      if(!MDNS.begin("sequenceall")) {
         Serial.println("Error starting mDNS");
         return;
    }
    MDNS.addService("http", "tcp", 80);

    AsyncCallbackJsonWebHandler* handleSTARequest = new AsyncCallbackJsonWebHandler("/set_sta", [](AsyncWebServerRequest *request, JsonVariant &json) {
    const JsonObject& jsonObject = json.as<JsonObject>();
        NVSService::writeStringToNVS(jsonObject["ssid"], jsonObject["password"]);
        request->send(200, "application/json", {});
    });

    AsyncCallbackJsonWebHandler* handleAPRequest = new AsyncCallbackJsonWebHandler("/set_ap", [](AsyncWebServerRequest *request, JsonVariant &json) {
    const JsonObject& jsonObject = json.as<JsonObject>();

        NVSService::writeStringToNVS(jsonObject["ssid"], jsonObject["password"]);
        request->send(200, "application/json", {});
    });

    serverPtr->addHandler(handleSTARequest);
    serverPtr->addHandler(handleAPRequest);
  }


  void initAP(const char * ssid, const char * password) {
    _doSetAP(ssid, password);
  }

private:

  AsyncWebServer *serverPtr;

  int _doSetSTA(const char * newSSID, const char *  newPassword) {
      WiFi.mode(WIFI_AP_STA);
      uint8_t numberNetworks = WiFi.scanNetworks();
      for(uint8_t i; i < numberNetworks; i++) {
          if (WiFi.SSID(i) == newSSID) {
            WiFi.begin(newSSID, newPassword);
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

  int _doSetAP(const char * ssid, const char *  password) {


    WiFi.softAP(ssid, password);
    return 1;
  }
};



#endif
