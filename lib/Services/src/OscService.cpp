#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService(WiFiUDP *Udp) {
    this->udp = Udp;

    WiFiService::getHostname(hostName);
    //WiFiService::getIpAddressFromHostname(ip);
}


void OscService::send(void *context, OscMsgChild & message) {
    reinterpret_cast<OscService *>(context)->udp->beginPacket(hostName, DEFAULT_REMOTE_UDP_PORT);
    message.send(*reinterpret_cast<OscService *>(context)->udp);
    reinterpret_cast<OscService *>(context)->udp->endPacket();
    message.empty();
}

bool OscService::receive(OscMsgChild &msg) {
    int size = udp->parsePacket();
    if (size > 0) {
        Serial.println("caught message in OscReceive");
        while (size--) {
            msg.fill(udp->read());
        }
        if (!msg.hasError()) {
            return true;
        }
    }
    return false;
}




