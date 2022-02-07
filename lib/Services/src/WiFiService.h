#ifndef WIFISERVICE_H
#define WIFISERVICE_H
#include <new>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "AsyncJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNSInterface.h>
#include "WiFiServiceInterface.h"
#include "NVSService.h"
#include "WifiCredentials.h"
#include "WifiErrorCodes.h"
#include <macros.h>


class WiFiService : public WiFiServiceInterface {
public:

    WiFiService(WiFiUDP *udp, AsyncWebServer *server, ESPmDNSInterface *mdns);

    ~WiFiService() override = default;

    WifiErrorCode begin() override;
    int oldState = 0;
    uint16_t interval = 2000;

    void handleWifiMode() override;

    WifiErrorCode getRemoteHostInfo() override;

    bool getRemoteIP(IPAddress ip) override;

    WiFiUDP *getUDP() override;

    char remoteHostName[32];
private:
    WiFiUDP *udp;
    ESPmDNSInterface *mdns;
    AsyncWebServer *server;

    IPAddress remoteIp = {0,0,0,0};
    IPAddress localIp = {0,0,0,0};
    const char * nvsNameSpace = "Wifi";
    bool _initWebServer();
    AsyncCallbackJsonWebHandler* _setAPCredentialsEndpoint();
    AsyncCallbackJsonWebHandler* _setSTACredentialsEndpoint();
    AsyncCallbackJsonWebHandler* _setRemoteHostNameEndpoint();
    AsyncCallbackJsonWebHandler* _setPrintDebugEndpoint();

    WifiErrorCode _initAP();

    WifiErrorCode _initSTA();

    bool _doSetSTA(const char *newSSID, const char *newPassword);

    bool _doSetAP(const char *ssid, const char *password);

    void _doHandleWifiMode();

    bool getRemoteHostname();

};


#endif
