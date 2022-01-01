//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_WIFISERVICEINTERFACE_H
#define SEQUENCEALL_WIFISERVICEINTERFACE_H

class WiFiServiceInterface {
public:

    virtual ~WiFiServiceInterface() = default;

    virtual void initAP() = 0;

    virtual bool initSTA() = 0;


    virtual void handleWifiMode() = 0;
    virtual char* getRemoteIP() = 0;

};
#endif //SEQUENCEALL_WIFISERVICEINTERFACE_H
