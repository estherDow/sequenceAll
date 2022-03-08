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

    if (!remoteIPs.empty() ) {
        _sendMSGToStoredIPs(message);
    }

    message.empty();
}

void OscService::_sendMSGToStoredIPs(OSCMessageInterface &message) {
    for (auto const& ip : remoteIPs) {
        if (ip[0] !=0){
            udp->beginPacket(ip, DEFAULT_REMOTE_UDP_PORT);
            Serial.println("message was sent");
            message.send(*udp);
            udp->endPacket();
        }
    }
}

void OscService::update(OSCMessageInterface &message) {
    doSend(message);
}

void OscService::addRemoteIP(void *context, OSCMessageInterface &instance, uint8_t offset) {

}



