//
// Created by Kenneth Dow on 29/12/21.
//

#ifndef SEQUENCEALL_ESPMDNSINTERFACE_H
#define SEQUENCEALL_ESPMDNSINTERFACE_H

class ESPmDNSInterface {
public:
    virtual MDNSResponder() = 0;
    virtual ~MDNSResponder() = 0;
    virtual bool begin(const char* hostName) = 0;
    virtual void end() = 0;

    virtual void setInstanceName(const char * name) = 0;
    virtual void setInstanceName(char * name) = 0;

    virtual bool addService(char *service, char *proto, uint16_t port) = 0;
    virtual bool addService(const char *service, const char *proto, uint16_t port) = 0;

    virtual bool addServiceTxt(char *name, char *proto, char * key, char * value) = 0;
    virtual void addServiceTxt(const char *name, const char *proto, const char *key,const char * value) = 0;
    virtual void addServiceTxt(String name, String proto, String key, String value) = 0;

    virtual void enableArduino(uint16_t port=3232, bool auth=false) = 0;
    virtual void disableArduino() = 0;

    virtual void enableWorkstation(wifi_interface_t interface=WIFI_IF_STA) = 0;
    virtual void disableWorkstation() = 0;

    virtual IPAddress queryHost(char *host, uint32_t timeout=2000) = 0;
    virtual IPAddress queryHost(const char *host, uint32_t timeout=2000)  = 0;
    virtual IPAddress queryHost(String host, uint32_t timeout=2000)  = 0;

    virtual int queryService(char *service, char *proto) = 0;
    virtual int queryService(const char *service, const char *proto) = 0;
    virtual int queryService(String service, String proto) = 0;

};
#endif //SEQUENCEALL_ESPMDNSINTERFACE_H
