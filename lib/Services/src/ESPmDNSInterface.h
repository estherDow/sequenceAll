//
// Created by Kenneth Dow on 29/12/21.
//

#ifndef SEQUENCEALL_ESPMDNSINTERFACE_H
#define SEQUENCEALL_ESPMDNSINTERFACE_H
#include <cstdint>
#include "IPAddressInterface.h"
class ESPmDNSInterface {
public:
    virtual ~ESPmDNSInterface() = default;
    virtual bool begin(const char* hostName) = 0;
    virtual void end() = 0;

    virtual void setInstanceName(const char * name) = 0;
    virtual void setInstanceName(char * name) = 0;

    virtual bool addService(char *service, char *protocol, uint16_t port) = 0;
    virtual bool addService(const char *service, const char *protocolcol, uint16_t port) = 0;

    virtual bool addServiceTxt(char *name, char *protocol, char * key, char * value) = 0;
    virtual void addServiceTxt(const char *name, const char *protocol, const char *key,const char * value) = 0;

    virtual IPAddressInterface queryHost(char *host, uint32_t timeout) = 0;
    virtual IPAddressInterface queryHost(const char *host, uint32_t timeout)  = 0;

    virtual int queryService(char *service, char *protocol) = 0;
    virtual int queryService(const char *service, const char *protocol) = 0;

};
#endif //SEQUENCEALL_ESPMDNSINTERFACE_H
