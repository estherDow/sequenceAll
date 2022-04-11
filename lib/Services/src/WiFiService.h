#ifndef WIFISERVICE_H
#define WIFISERVICE_H
#include <new>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include "AsyncJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNSInterface.h>
#include "ESPmDNSAdapter.h"
#include "WiFiServiceInterface.h"
#include "NVSService.h"
#include "WifiCredentials.h"
#include "WifiErrorCodes.h"
#include <macros.h>



class WiFiService : public WiFiServiceInterface {
public:

    WiFiService();

    ~WiFiService() override = default;

    WifiErrorCode begin(const char *ssid, const char *password, WifiMode mode) override;
    int oldState = 0;
    uint16_t interval = 2000;

    AsyncUDP *getUDP() override;

    char remoteHostName[32];
private:
    AsyncUDP *udp;
    ESPmDNSInterface *mdns;
    AsyncWebServer *server;

    IPAddress remoteIp = {0,0,0,0};
    IPAddress localIp = {0,0,0,0};
    const char * nvsNameSpace = "Wifi";
    bool _initWebServer();
    AsyncCallbackJsonWebHandler* _setAPCredentialsEndpoint();
    AsyncCallbackJsonWebHandler* _setSTACredentialsEndpoint();

    AsyncCallbackJsonWebHandler* _setPrintDebugEndpoint();

    WifiErrorCode _initAP(WiFiCredentialsChar defaultCredentials);
    WifiErrorCode _initSTA(WiFiCredentialsChar &defaultCredentials);

    bool _doSetAP(WiFiCredentialsChar &credentials);
    bool _doSetSTA(WiFiCredentialsChar &credentials);

};


#endif
