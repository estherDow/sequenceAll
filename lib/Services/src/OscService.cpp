#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService(WiFiUDP *Udp) {
    this->udp = Udp;
}


void OscService::send(void *context, const char *uri, uint8_t argument) {
    //TODO: Find method prototype
    OscMsgChild msg(uri);
    msg.add(argument);
    reinterpret_cast<OscService *>(context)->udp->beginPacket();
    msg.send(*reinterpret_cast<OscService *>(context)->udp);
    reinterpret_cast<OscService *>(context)->udp->endPacket();
    msg.empty();
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




