#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include "WiFi.h"
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoNvs.h>

#include <Module.h>
#include <macros.h>

class OscService : public Module {
public:
    OscService();

    void begin(WiFiUDP *udp);

    static void send(void * context, const char * uri, uint8_t argument);
    OSCMessage receive();
    void update(OscMsgChild & message) override{};
private:

    WiFiUDP* Udp;
    static IPAddress * remoteIP;
    IPAddress testIP;
    IPAddress _getIpAddressFromHostname();
};

#endif
