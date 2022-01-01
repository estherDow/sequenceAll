#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <Arduino.h>
#include <ArduinoNvs.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNSInterface.h>
#include <WebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "../../../.pio/libdeps/esp32dev/ESP Async WebServer/src/ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "WiFiServiceInterface.h"
#include <macros.h>



class WiFiService : public WiFiServiceInterface{
public:
    WiFiUDP UDP;

    ~WiFiService() override = default;
    explicit WiFiService(ESPmDNSInterface &mdns);

    void initAP() override;

    bool initSTA() override;

    int oldState = 0;
    uint16_t interval = 2000;
    void handleWifiMode() override;
    char* getRemoteIP() override;

    IPAddress Ip;
    String hostName;
private:
    AsyncWebServer *server{};

    bool _doSetSTA(String newSSID, String newPassword);
    bool _doSetAP(String ssid, String password);
    void _doHandleWifiMode();
};


#endif
