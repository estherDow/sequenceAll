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
#include "../../../.pio/libdeps/esp32dev/ESP Async WebServer/src/ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <macros.h>



class WiFiService {
public:
    WiFiUDP UDP;

    explicit WiFiService();

    void initAP();

    bool initSTA();

    int oldState = 0;
    uint16_t interval = 2000;
    void handleWifiMode();
    String getHostname();

    IPAddress Ip;
    String hostName;
private:
    AsyncWebServer *server{};

    bool _doSetSTA(String newSSID, String newPassword);
    bool _doSetAP(String ssid, String password);
    void _doHandleWifiMode();
};


#endif
