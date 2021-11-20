#include "Oscservice.h"

OscService::OscService(){
    Udp = new WiFiUDP();
    Udp->begin(LOCAL_UDP_PORT);
    remoteIP = _getIpAddressFromHostname();

}

void OscService::send(String uri, uint8_t argument) {
    OSCMessage msg(uri);
    msg.add(argument);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}

void OscService::receive() {
    OSCMessage msg;
    int size = Udp.parsePacket();

    if (size > 0) {
        while (size--) {
            msg.fill(Udp.read());
        }
        if (!msg.hasError()) {
            Serial.println(msg.getInt(0));
        }
    }
}


IPAddress OscService::_getIpAddressFromHostname() {
    hostname = NVSService::readStringFromNVS("remoteHostname");
    if (hostname.length() == 0 ) {
        hostname == DEFAULT_REMOTE_HOSTNAME;
    }
        return MDNS.queryHost((char *) hostname.c_str(), uint32_t timeout=2000);

}
