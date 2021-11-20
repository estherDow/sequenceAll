#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <ESPmDNS.h>

#include "IOInterface.h"
#include <Module.h>
#include <NVSService.h>
#include <macros.h>

class OscService : public IOInterface, public Module {
public:
    OscService();

    void send(String uri, uint8_t argument);
    void receive();

private:
    WiFiUDP* Udp;
    IPAddress remoteIP;
    IPAddress _getIpAddressFromHostname();
};

#endif
