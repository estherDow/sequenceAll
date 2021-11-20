#include "OscService.h"

OscService::OscService(){
    Udp = new WiFiUDP();
    Udp->begin(LOCAL_UDP_PORT);
    remoteIP = _getIpAddressFromHostname();

}

void OscService::send(String uri, uint8_t argument) {
    //TODO: Find method prototype
    OSCMessage msg((char *) uri.c_str());
    msg.add(argument);
    Udp->beginPacket(remoteIP, DEFAULT_REMOTE_UDP_PORT);
    msg.send(*Udp);
    Udp->endPacket();
    msg.empty();
}

void OscService::receive() {
    OSCMessage msg;
    int size = Udp->parsePacket();

    if (size > 0) {
        while (size--) {
            msg.fill(Udp->read());
        }
        if (!msg.hasError()) {
            Serial.println(msg.getInt(0));
        }
    }
}


IPAddress OscService::_getIpAddressFromHostname() {
    String hostname = NVSService::readStringFromNVS("remoteHostname");
    if (hostname.length() == 0 ) {
        hostname == DEFAULT_REMOTE_HOSTNAME;
    }
        return MDNS.queryHost((char *) hostname.c_str(), 2000);

}
