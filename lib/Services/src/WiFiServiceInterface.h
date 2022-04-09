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

class WiFiServiceInterface {
public:

    virtual ~WiFiServiceInterface() = default;

    virtual WifiErrorCode begin() = 0;

    virtual AsyncUDP *getUDP() = 0;
};

#endif //SEQUENCEALL_WIFISERVICEINTERFACE_H
