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


    void send(void * context, const char * uri, uint8_t argument);
    bool receive(OscMsgChild & message);
    void update(OscMsgChild & message) override{};
    static IPAddress ipAddress(192, 168, 122, 252);
private:
    WiFiUDP *udp;
};

#endif
