#include "OscService.h"

//TODO Ceck if any of the arguments may be removed
OscService::OscService( WiFiServiceInterface *wiFi) : udp(wiFi->getUDP()), wiFi(wiFi) {
    if (udp->listen(8000)) {Serial.println("UDP listening on port 8000");}
    udp->onPacket(parseMessage, this);
}


void OscService::send(void *context, OSCMessageInterface & message) {
    Serial.println("osc.send was called");
    reinterpret_cast<OscService *>(context)->doSend(message);
}



void OscService::parseMessage(void *context, AsyncUDPPacket packet) {
    reinterpret_cast<OscService *>(context)->addRemoteIP(packet);
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

void OscService::update(OSCMessageInterface &message) {
    doSend(message);
}
void OscService::doSend(OSCMessageInterface &message) {
    AsyncUDPMessage asyncUdpMessage;
    udp->broadcastTo(asyncUdpMessage, DEFAULT_REMOTE_UDP_PORT);


    if (!remoteIPs.empty() ) {
        message.send(asyncUdpMessage);
        udp->broadcastTo(asyncUdpMessage, DEFAULT_REMOTE_UDP_PORT);

        for (auto const &ip: remoteIPs) {
            if (ip[0] != 0) {
                udp->sendTo(asyncUdpMessage, ip, DEFAULT_REMOTE_UDP_PORT, TCPIP_ADAPTER_IF_AP);
                Serial.println("message was sent");
            }
        }
    }

    message.empty();
}

void OscService::addRemoteIP(AsyncUDPPacket packet) {
    IPAddress remoteIP = packet.remoteIP();
    auto remoteIPIterator = std::find(remoteIPs.begin(), remoteIPs.end(), remoteIP);
    if (remoteIP != *remoteIPIterator) {
        remoteIPs.push_back(remoteIP);
        Serial.println("IP Address was added to list");
    }
}






