#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include "WiFi.h"
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoNvs.h>
#include "WiFiService.h"
#include <Module.h>
#include <macros.h>


class OscService : public Module {
public:
    explicit OscService(WiFiUDP *udp);



    static void send(void * context, OscMsgChild & message);
    bool receive(OscMsgChild & message);
    void update(OscMsgChild & message) override{};
    const char * hostName;
private:
    WiFiUDP *udp;
};

#endif
