#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService(WiFiService *wifi) {
    this->udp = &wifi->UDP;
    this->wiFi = wifi;
}


void OscService::send(void *context, OSCMessageInterface & message) {
    Serial.println("osc.send was called");
    reinterpret_cast<OscService *>(context)->doSend(message);
}

bool OscService::receive(OSCMessageInterface &msg) {
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

void OscService::doSend(OSCMessageInterface &message) {
    Serial.println("DoSend was called this is hostname:");
    Serial.println(hostName);
    udp->beginPacket(wiFi->Ip,DEFAULT_REMOTE_UDP_PORT);
    message.send(* udp);
    udp->endPacket();
    message.empty();
}

void OscService::update(OSCMessageInterface &message) {
    doSend(message);
}



