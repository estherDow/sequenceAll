//
// Created by Kenneth Dow on 29/12/21.
//

#ifndef SEQUENCEALL_ESPMDNSADAPTER_H
#define SEQUENCEALL_ESPMDNSADAPTER_H
#include "ESPmDNSInterface.h"
#include <ESPmDNS.h>

class ESPmDNSAdapter : public ESPmDNSInterface{
public:
    ~ESPmDNSAdapter(){};
    bool begin(const char* hostName) override;
    void end() override;

    void setInstanceName(const char * name) override;
    void setInstanceName(char * name) override;

    bool addService(char *service, char *protocol, uint16_t port) override;
    bool addService(const char *service, const char *proto, uint16_t port) override;


    bool addServiceTxt(char *name, char *protocol, char * key, char * value) override;
    void addServiceTxt(const char *name, const char *protocol, const char *key,const char * value) override;



    IPAddress queryHost(char *host, uint32_t timeout) override;
    IPAddress queryHost(const char *host, uint32_t timeout) override;

    int queryService(char *service, char *protocol) override;
    int queryService(const char *service, const char *protocol) override;


};


#endif //SEQUENCEALL_ESPMDNSADAPTER_H
