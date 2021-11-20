#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include "IOInterface.h"
#include <Module.h>
#include <NVSService.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <macros.h>

class OscService : public IOInterface, public Module {
public:
    OscService();

    void send();
    void receive();

private:
    WiFiUDP* Udp;
    IPAddress remoteIP;
    IPAddress _getIpAddressFromHostname();
};

#endif
