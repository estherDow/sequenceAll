//
// Created by Kenneth Dow on 28/12/21.
//

#ifndef SEQUENCEALL_RECIPIENTADDRESS_H
#define SEQUENCEALL_RECIPIENTADDRESS_H
#include <cstdint>

class OSCMessageInterface;

typedef struct RecipientAddress {
    void *context;
    const char *pattern;
    void (*callback)(void *context, OSCMessageInterface &instance, uint8_t offset);
    int offset;
    RecipientAddress(void *classContext,
    const char *AddressPattern,
    void (*staticCallback)(void *context, OSCMessageInterface &instance, uint8_t offset),
    int matchOffset
    ) : context(classContext), pattern(AddressPattern), callback(staticCallback), offset(matchOffset){}
} RecipientAddress;

#endif //SEQUENCEALL_RECIPIENTADDRESS_H
