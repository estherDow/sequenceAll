#ifndef OSCSERVICE_H
#define OSCSERVICE_H

#include <Arduino.h>
#include "WiFiServiceInterface.h"
#include <Module.h>
#include <macros.h>
#include <algorithm>
#include "OscMessageAdapter.h"

class OscService : public Module {
public:
    explicit OscService(WiFiServiceInterface *wiFi);

    static void send(void *context, OSCMessageInterface &message);

    void doSend(OSCMessageInterface &message);

    bool receive();

    void update(OSCMessageInterface &message) override;

    static void parseMessage(void *context, AsyncUDPPacket packet);


    static void addRemoteIP(void *context, OSCMessageInterface &instance, uint8_t offset);

    const char *hostName{};
private:
    AsyncUDP *udp;
    WiFiServiceInterface *wiFi;
    std::list<IPAddress> remoteIPs;
};

#endif
