//
// Created by Kenneth Dow on 29/12/21.
//

#ifndef SEQUENCEALL_ESPMDNSADAPTER_H
#define SEQUENCEALL_ESPMDNSADAPTER_H
#include "ESPmDNSInterface.h"
#include <ESPmDNS.h>

class ESPmDNSAdapter : public ESPmDNSInterface{
public:
    ~MDNSResponder(){};
    bool begin(const char* hostName) override;
    void end() override;

    void setInstanceName(const char * name) override;
    void setInstanceName(char * name) override;

    bool addService(char *service, char *protocol, uint16_t port) override;
    bool addService(const char *service, const char *proto, uint16_t port) override;


    bool addServiceTxt(char *name, char *proto, char * key, char * value);
    void addServiceTxt(const char *name, const char *proto, const char *key,const char * value){
        addServiceTxt((char *)name, (char *)proto, (char *)key, (char *)value);
    }
    void addServiceTxt(String name, String proto, String key, String value){
        addServiceTxt(name.c_str(), proto.c_str(), key.c_str(), value.c_str());
    }

    void enableArduino(uint16_t port=3232, bool auth=false);
    void disableArduino();

    void enableWorkstation(wifi_interface_t interface=WIFI_IF_STA);
    void disableWorkstation();

    IPAddress queryHost(char *host, uint32_t timeout=2000);
    IPAddress queryHost(const char *host, uint32_t timeout=2000){
        return queryHost((char *)host, timeout);
    }
    IPAddress queryHost(String host, uint32_t timeout=2000){
        return queryHost(host.c_str(), timeout);
    }

    int queryService(char *service, char *proto);
    int queryService(const char *service, const char *proto){
        return queryService((char *)service, (char *)proto);
    }
    int queryService(String service, String proto){
        return queryService(service.c_str(), proto.c_str());
    }

    String hostname(int idx);
    IPAddress IP(int idx);
    IPv6Address IPv6(int idx);
    uint16_t port(int idx);
    int numTxt(int idx);
    bool hasTxt(int idx, const char * key);
    String txt(int idx, const char * key);
    String txt(int idx, int txtIdx);

};


#endif //SEQUENCEALL_ESPMDNSADAPTER_H
