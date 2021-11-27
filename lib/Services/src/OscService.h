#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <ESPmDNS.h>
#include <ArduinoNvs.h>

#include "IOInterface.h"
#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
#include <Module.h>
#include <macros.h>

class OscService : public IOInterface, public Module {
public:
    OscService();

    void begin(WiFiUDP *udp);

    void send(const String& uri, uint8_t argument);
    OSCMessage receive();
    void update(SignalTypes sender, int msg);
private:

    WiFiUDP* Udp;
    IPAddress remoteIP;
    IPAddress _getIpAddressFromHostname();


};

#endif
