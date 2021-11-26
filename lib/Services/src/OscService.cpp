#include "OscService.h"

void OscService::begin(WiFiUDP* udp){
    Udp = udp;
    remoteIP = _getIpAddressFromHostname();
}

OscService::OscService() {
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
            int message = msg.getInt(0);
            Serial.println(message);
        }
    }
}

void OscService::update(SignalTypes sender, int msg) {
    return;
}


IPAddress OscService::_getIpAddressFromHostname() {
    String hostname = NVSService::readStringFromNVS("remoteHostname");
    if (hostname.length() == 0 ) {
        hostname = DEFAULT_REMOTE_HOSTNAME;
    }
        return MDNS.queryHost((char *) hostname.c_str(), 2000);

}

