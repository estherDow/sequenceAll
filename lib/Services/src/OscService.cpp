#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService( WiFiServiceInterface &wiFi) : udp(wiFi.getUDP()), wiFi(wiFi) {

}


void OscService::send(void *context, OSCMessageInterface & message) {
    Serial.println("osc.send was called");
    reinterpret_cast<OscService *>(context)->doSend(message);
}

bool OscService::receive() {
    OSCMessage message;
    OscMessageAdapter msg(message);

    int size = udp->parsePacket();
    if (size > 0) {
        remoteIP = udp->remoteIP();

        while (size--) {
            msg.fill(udp->read());
        }
        if (!msg.hasError()){
            notify(msg);
            return true;
        }
    }
    return false;
}

void OscService::doSend(OSCMessageInterface &message) {

    if (remoteIP[0] !=0){
        udp->beginPacket(remoteIP, DEFAULT_REMOTE_UDP_PORT);
        message.send(*udp);
        udp->endPacket();
    }
}



void OscService::update(OSCMessageInterface &message) {
    doSend(message);
}

void OscService::addRemoteIP(void *context, OSCMessageInterface &instance, uint8_t offset) {

}



