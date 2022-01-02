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



class WiFiService : public WiFiServiceInterface{
public:

    ~WiFiService() override = default;
    explicit WiFiService(
            WiFiUDP * UDP,
            ESPmDNSInterface * mdns,
            NVSServiceInterface * nvs
            );

    void initAP() override;

    bool initSTA() override;

    int oldState = 0;
    uint16_t interval = 2000;
    void handleWifiMode() override;
    IPAddress getRemoteIP() override;

    const char* hostName;
private:
    AsyncWebServer *server{};

    bool _doSetSTA(char * newSSID, char * newPassword);
    bool _doSetAP(char * ssid, char * password);
    void _doHandleWifiMode();

    const char *getHostname();
};


#endif
