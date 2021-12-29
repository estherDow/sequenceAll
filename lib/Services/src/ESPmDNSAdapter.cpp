//
// Created by Kenneth Dow on 29/12/21.
//

#include "ESPmDNSAdapter.h"

bool ESPmDNSAdapter::begin(const char *hostName) {
    return MDNS.begin(hostName);
}

void ESPmDNSAdapter::end() {
    MDNS.end();
}

void ESPmDNSAdapter::setInstanceName(const char *name) {
    MDNS.setInstanceName(name);
}

void ESPmDNSAdapter::setInstanceName(char *name) {
    MDNS.setInstanceName(name);

}

bool ESPmDNSAdapter::addService(char *service, char *protocol, uint16_t port) {
    return MDNS.addService(service,protocol,port);
}
