#include "OscService.h"
#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"

void OscService::begin(WiFiUDP *udp) {
    Udp = udp;
    remoteIP = _getIpAddressFromHostname();
}

OscService::OscService() {
}

void OscService::send(const String& uri, uint8_t argument) {
    //TODO: Find method prototype
    OSCMessage msg((char *) uri.c_str());
    msg.add(argument);
    Udp->beginPacket(remoteIP, DEFAULT_REMOTE_UDP_PORT);
    msg.send(*Udp);
    Udp->endPacket();
    msg.empty();
}

OSCMessage OscService::receive() {
    int size = Udp->parsePacket();
    OSCMessage msg;
    if (size > 0) {
        while (size--) {
            msg.fill(Udp->read());
        }
        if (!msg.hasError()) {
            return msg;
        }
    }
    return ;
}

//void OscService::_doReceive() {

//    if (_msg.isInt(0)) {
//        _iMessage = _msg.getInt(0);
//    }
//    if (_msg.isString(0)) {
//        _msg.getString(0,_cMessage,32);
//    }
//    if (_msg.isFloat(0)) {
//        _fMessage = _msg.getFloat(0);
//    }
//    }
//}

void OscService::update(SignalTypes sender, int msg) {
}


IPAddress OscService::_getIpAddressFromHostname() {
    String hostname = NVS.getString("remoteHostname");
    if (hostname.length() == 0) {
        hostname = DEFAULT_REMOTE_HOSTNAME;
    }
    return MDNS.queryHost((char *) hostname.c_str(), 2000);

}

