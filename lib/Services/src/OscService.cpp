#include "OscService.h"

//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
OscService::OscService( WiFiServiceInterface &wiFi) : udp(wiFi.getUDP()), wiFi(wiFi) {
    udp->onPacket(parseMessage, this);
}


void OscService::send(void *context, OSCMessageInterface & message) {
    Serial.println("osc.send was called");
    reinterpret_cast<OscService *>(context)->doSend(message);
}

bool OscService::receive() {
    OSCMessage message;
    OscMessageAdapter msg(message);
    if (udp->listen(8000)) {


    }

    return false;
}


void OscService::parseMessage(void *context, AsyncUDPPacket packet) {
    IPAddress remoteIP = packet.remoteIP();
    auto remoteIPIterator = std::find(reinterpret_cast<OscService *>(context)->remoteIPs.begin(), reinterpret_cast<OscService *>(context)->remoteIPs.end(), remoteIP);
    if (remoteIP != *remoteIPIterator) {
        reinterpret_cast<OscService *>(context)->remoteIPs.push_back(remoteIP);
        Serial.println("IP Address was added to list");
    }
    OSCMessage message;
    OscMessageAdapter msg(message);
    size_t packetLength = packet.length();
    uint8_t * packetData = packet.data();
    for (int i = 0;i < packetLength; i++) {
        msg.fill(packetData[i]);
    }
    if (!msg.hasError()){
        reinterpret_cast<OscService *>(context)->notify(msg);
    }
    else {
        Serial.println("OSCMessage has error");
    }

}


void OscService::doSend(OSCMessageInterface &message) {

    if (!remoteIPs.empty() ) {
        _broadcastMSG(message);
    }

    message.empty();
}

void OscService::_broadcastMSG(OSCMessageInterface &message) {
            AsyncUDPMessage asyncUdpMessage;
            message.send(asyncUdpMessage);
            udp->broadcast(asyncUdpMessage);
}

void OscService::update(OSCMessageInterface &message) {
    doSend(message);
}

void OscService::addRemoteIP(void *context, OSCMessageInterface &instance, uint8_t offset) {

}






