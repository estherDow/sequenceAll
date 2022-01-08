#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include "WiFiServiceInterface.h"
#include <Module.h>
#include <macros.h>


class OscService : public Module {
public:
    explicit OscService(WiFiUDP &udp, WiFiServiceInterface &wiFi);

    static void send(void *context, OSCMessageInterface &message);
    void doSend(OSCMessageInterface &message);
    bool receive(OSCMessageInterface &message);

    void update(OSCMessageInterface &message) override;
    const char * hostName{};
private:
    WiFiUDP &udp;
    WiFiServiceInterface &wiFi;
};

#endif
