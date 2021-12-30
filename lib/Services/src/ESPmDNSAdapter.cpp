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

bool ESPmDNSAdapter::addService(const char *service, const char *protocol, uint16_t port) {
    return MDNS.addService(service,protocol,port);
}

bool ESPmDNSAdapter::addServiceTxt(char *name, char *protocol, char *key, char *value) {
    return MDNS.addServiceTxt(name, protocol, key, value);
}

void ESPmDNSAdapter::addServiceTxt(const char *name, const char *protocol, const char *key, const char *value) {
    return MDNS.addServiceTxt(name, protocol, key, value);
}

IPAddress ESPmDNSAdapter::queryHost(char *host, uint32_t timeout) {
    return MDNS.queryHost(host, timeout);
}

IPAddress ESPmDNSAdapter::queryHost(const char *host, uint32_t timeout) {
    return MDNS.queryHost(host, timeout);
}

int ESPmDNSAdapter::queryService(char *service, char *protocol) {
    return MDNS.queryService(service, protocol);
}

int ESPmDNSAdapter::queryService(const char *service, const char *protocol) {
    return MDNS.queryService(service, protocol);
}



