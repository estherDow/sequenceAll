//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_WIFISERVICEINTERFACE_H
#define SEQUENCEALL_WIFISERVICEINTERFACE_H


class WiFiUDP;
class IPAddress;
class NVSServiceInterface;
class ESPmDNSInterface;

class WiFiServiceInterface {
public:
    WiFiUDP * udp{};
    ESPmDNSInterface * mdns{};
    NVSServiceInterface * nvs{};

    IPAddress * Ip{};

    virtual ~WiFiServiceInterface() = default;

    virtual void initAP() = 0;

    virtual bool initSTA() = 0;


    virtual void handleWifiMode() = 0;
    virtual IPAddress getRemoteIP() = 0;

};
#endif //SEQUENCEALL_WIFISERVICEINTERFACE_H
