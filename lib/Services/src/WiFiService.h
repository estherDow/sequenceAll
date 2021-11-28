#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <Arduino.h>
#include <ArduinoNvs.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <macros.h>



class WiFiService {
public:
    WiFiUDP UDP;
    explicit WiFiService() {

//TODO:PROPER ERROR HANDLING MY G
        if(!initSTA()) {
        initAP();
        }
        IPAddress ipAddress = getIpAddressFromHostname();
        UDP.begin(LOCAL_UDP_PORT);
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
                        NVS.setString(
                                "STAssid",
                                jsonObject["ssid"]);
                        NVS.setString(
                                "STApassword",
                                jsonObject["password"]);
                    }

                    NVS.setInt(
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
                        NVS.setString(
                                "APssid",
                                jsonObject["ssid"]);
                        NVS.setString(
                                "APpassword",
                                jsonObject["password"]);
                    }

                    NVS.setInt(
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
        WiFi.mode(WIFI_AP);
        String ssid = NVS.getString("APssid");
        String password = NVS.getString("APpassword");
        if (ssid.length() == 0) {
            ssid = DEFAULT_AP_SSID;
            password = DEFAULT_AP_PASSWORD;
        }
        _doSetAP(ssid, password);
    }

    bool initSTA() {
        WiFi.mode(WIFI_STA);
        uint8_t numberNetworks = WiFi.scanNetworks();
        String ssid = NVS.getString("STAssid");
        String password = NVS.getString("STApassword");
        if (ssid.length() == 0) {
            return false;
        }
        for (uint8_t i = 0; i < numberNetworks; i++) {
            if (WiFi.SSID(i) == (char *) ssid.c_str()) {
                _doSetSTA(ssid, password);
                return true;
            }
        }
        return false;
    }

    int oldState = 0;
    int interval = 2000;

    void handleWifiMode() {
        int currentstate = millis();
        if (currentstate > oldState + interval) {
            _doHandleWifiMode();
            oldState += interval;
        }
    }

    IPAddress getIpAddressFromHostname() {
        String hostname = NVS.getString("remoteHostname");
        if (hostname.length() == 0) {
            hostname = DEFAULT_REMOTE_HOSTNAME;
        }
        IPAddress ip = MDNS.queryHost((char *) hostname.c_str(), 2000);

        uint8_t firstOctet = ip.operator[](1);
        if (firstOctet == 0) {
            ip.operator=(defaultIpAddress);
        }
        return ip;
    }

private:

    const uint32_t defaultIpAddress = 19216814;

    AsyncWebServer *server{};

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

        if (NVS.getInt("SetAP")) {
            initAP();
            NVS.setInt(
                    "SetAP",
                    0);
        }
        if (NVS.getInt("SetSTA")) {
            if (!initSTA()) {
                initAP();
            }

            NVS.setInt(
                    "SetSTA",
                    0);
        }
    }
};


#endif
