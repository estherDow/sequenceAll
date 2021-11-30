#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService(WiFiUDP *Udp) {
    this->udp = Udp;

    WiFiService::getHostname(hostName);
}


void OscService::send(void *context, OscMsgChild & message) {
    reinterpret_cast<OscService *>(context)->doSend(message);
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

void OscService::doSend(OscMsgChild &message) {

    udp->beginPacket(hostName, DEFAULT_REMOTE_UDP_PORT);
    message.send(* udp);
    udp->endPacket();
    message.empty();
}



