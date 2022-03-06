//
// Created by Kenneth Dow on 28/12/21.
//

#ifndef SEQUENCEALL_OSCMESSAGEINTERFACE_H
#define SEQUENCEALL_OSCMESSAGEINTERFACE_H
#include "RecipientAddress.h"
#include "WiFiService.h"

class OSCMessageInterface {
public:
    virtual ~OSCMessageInterface() = default;
    virtual bool dispatch(
            RecipientAddress &address
            ) = 0;

    virtual bool route(
            RecipientAddress &address
            ) = 0;

    virtual void empty() = 0;
    virtual void fill(uint8_t) = 0;
    virtual bool fullMatch( const char * pattern, int) = 0;
    virtual int getDataLength(int position) =0;
    virtual int32_t getInt(int position) = 0;
    virtual int getString(int position, char * buffer, int length) = 0;
    virtual bool hasError() = 0;
    virtual bool isInt(int sample) = 0;
    virtual bool isString(int position) = 0;
    virtual void send(WiFiUDP &udp) = 0;
    virtual  uint8_t getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset) = 0;

    virtual OSCMessage setAddress(const char * _address) = 0;
};


#endif //SEQUENCEALL_OSCMESSAGEINTERFACE_H
