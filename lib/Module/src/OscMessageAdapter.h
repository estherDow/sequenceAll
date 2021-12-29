//
// Created by Kenneth Dow on 28/11/21.
//

#ifndef SEQUENCEALL_OSCMESSAGEADAPTER_H
#define SEQUENCEALL_OSCMESSAGEADAPTER_H

#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
#include "OSCMessageInterface.h"

class OscMessageAdapter : public OSCMessageInterface {
public:


    explicit OscMessageAdapter(OSCMessage &message);

    ~OscMessageAdapter() override = default;

    bool dispatch(RecipientAddress &address) override;

    bool route(RecipientAddress &address) override;

    void empty() override;
    void fill(uint8_t byteStream) override;
    bool fullMatch(const char *pattern, int offset) override;
    int getDataLength(int position) override;
    int getString(int position, char * buffer, int length) override;
    bool hasError() override;
    int32_t getInt(int position) override;
    bool isInt(int sample) override;
    bool isString(int position) override;
    void send(WiFiUDP &udp) override;

    uint8_t getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset) override; //returns new offset and overwrites handle
private:
    OSCMessage &_message;
};


#endif //SEQUENCEALL_OSCMESSAGEADAPTER_H
