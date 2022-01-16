#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WebServer.h>
#include "AsyncJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJsonHandler.h"
#include <ESPmDNSInterface.h>
#include "WiFiServiceInterface.h"
#include "NVSService.h"
#include "WifiCredentials.h"
#include <macros.h>


class WiFiService : public WiFiServiceInterface {
public:

    WiFiService(WiFiUDP &udp, AsyncWebServer &server, ESPmDNSInterface &mdns);

    ~WiFiService() override = default;

    bool begin() override;
    int oldState = 0;
    uint16_t interval = 2000;

    void handleWifiMode() override;

    IPAddress getRemoteIP() override;

    WiFiUDP &getUDP() override;

    const char *hostName;
private:
    WiFiUDP &udp;
    ESPmDNSInterface &mdns;

    IPAddress remoteIp;
    AsyncWebServer &server;
    const char * nvsNameSpace = "Wifi";
    bool _initWebServer();

    bool _initAP();

    bool _initSTA();

    bool _doSetSTA(const char *newSSID, const char *newPassword);

    bool _doSetAP(const char *ssid, const char *password);

    void _doHandleWifiMode();

    const char *getHostname();
};


#endif
