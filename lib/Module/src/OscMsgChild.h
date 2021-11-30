//
// Created by Kenneth Dow on 28/11/21.
//

#ifndef SEQUENCEALL_OSCMSGCHILD_H
#define SEQUENCEALL_OSCMSGCHILD_H

#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"

class OscMsgChild : public OSCMessage {
public:
    char * sender;

    explicit OscMsgChild(const char * address,  char * sender) : OSCMessage (address){ this->sender = sender;};
    OscMsgChild() : OSCMessage(){};

    bool dispatch(
            void *context,
            const char *pattern,
            void (*callback)(void *context,OscMsgChild &),
            int addr_offset
    );

    bool route(
            void * context,
            const char *pattern,
            void (*callback)(void *context, OscMsgChild &, uint8_t),
            int initial_offset
    );

    uint8_t getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset); //returns new offset and overwrites handle
};


#endif //SEQUENCEALL_OSCMSGCHILD_H
