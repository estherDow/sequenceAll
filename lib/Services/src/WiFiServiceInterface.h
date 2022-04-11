//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_WIFISERVICEINTERFACE_H
#define SEQUENCEALL_WIFISERVICEINTERFACE_H
#include "WifiErrorCodes.h"


class ESPAsyncWebServer;

class AsyncUDP;

class IPAddress;

class NVSServiceInterface;

class ESPmDNSInterface;

typedef enum {
    MODE_STA,
    MODE_AP
}WifiMode;

class WiFiServiceInterface {
public:

    virtual ~WiFiServiceInterface() = default;

    virtual WifiErrorCode begin(const char *ssid, const char *password, WifiMode mode) = 0;

    virtual AsyncUDP *getUDP() = 0;
};

#endif //SEQUENCEALL_WIFISERVICEINTERFACE_H
