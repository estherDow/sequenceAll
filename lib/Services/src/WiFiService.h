#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "../../../.pio/libdeps/esp32dev/ESP Async WebServer/src/ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ESPmDNSInterface.h>
#include "WiFiServiceInterface.h"
#include "NVSServiceInterface.h"
#include <macros.h>


class WiFiService : public WiFiServiceInterface {
public:

    WiFiService(WiFiUDP &udp, AsyncWebServer &server, ESPmDNSInterface &mdns, NVSServiceInterface &nvs);

    ~WiFiService() override = default;

    int oldState = 0;
    uint16_t interval = 2000;

    void handleWifiMode() override;

    IPAddress getRemoteIP() override;

    WiFiUDP &getUDP() override;

    const char *hostName;
private:
    WiFiUDP &udp;
    ESPmDNSInterface &mdns;
    NVSServiceInterface &nvs;

    IPAddress remoteIp;
    AsyncWebServer &server;

    bool _initAP();

    bool _initSTA();

    bool _doSetSTA(char *newSSID, char *newPassword);

    bool _doSetAP(char *ssid, char *password);

    void _doHandleWifiMode();

    const char *getHostname();
};


#endif
