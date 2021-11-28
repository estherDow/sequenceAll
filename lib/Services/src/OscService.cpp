#include "OscService.h"
#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
//TODO: queryHost returns an IPAddress with noargs Constructor. better error check
void OscService::begin(WiFiUDP *udp) {
    Udp = udp;
    *remoteIP = _getIpAddressFromHostname();
    if (*remoteIP == testIP) {
        remoteIP = new IPAddress(192,168,1,4);
    }
}

OscService::OscService() {
}

void OscService::send(void *context, const char *uri, uint8_t argument) {
    //TODO: Find method prototype
    OSCMessage msg(uri);
    msg.add(argument);
    reinterpret_cast<OscService *>(context)->Udp->beginPacket(*remoteIP, DEFAULT_REMOTE_UDP_PORT);
    msg.send(*reinterpret_cast<OscService *>(context)->Udp);
    reinterpret_cast<OscService *>(context)->Udp->endPacket();
    msg.empty();
}

//TODO: find better error handling here.
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
    return msg;
}


IPAddress OscService::_getIpAddressFromHostname() {
    String hostname = NVS.getString("remoteHostname");
    if (hostname.length() == 0) {
        hostname = DEFAULT_REMOTE_HOSTNAME;
    }
    return MDNS.queryHost((char *) hostname.c_str(), 2000);

}

