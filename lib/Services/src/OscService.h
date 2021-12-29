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
    explicit OscService(WiFiService *wifi);

    static void send(void *context, OSCMessageInterface &message);
    void doSend(OSCMessageInterface &message);
    bool receive(OSCMessageInterface &message);

    void update(OSCMessageInterface &message) override;
    const char * hostName{};
private:
    WiFiUDP *udp{};
    WiFiService *wiFi;
};

#endif
