//
// Created by Kenneth Dow on 28/11/21.
//

#include "OscMsgChild.h"


//Send one to one

bool OscMsgChild::dispatch(void *context, const char * pattern, void (*callback)( void *context, OscMsgChild &), int addr_offset){
    if (fullMatch(pattern, addr_offset)){
        callback(context,*this);
        return true;
    } else {
        return false;
    }
}

bool OscMsgChild::route(void *context, const char * pattern, void (*callback)( void *context, OscMsgChild &, uint8_t), int initial_offset){
    int match_offset = match(pattern, initial_offset);
    if (match_offset>0){
        callback(context, *this, match_offset + initial_offset);
        return true;
    } else {
        return false;
    }
}

uint8_t OscMsgChild::getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset) {
    char addr[32];
    uint8_t DefaultOffset = 1; //offset to account for "/"
    uint8_t NewOffset = DefaultOffset + offset;
    getAddress(addr, NewOffset);
    Serial.printf("Address received at getAddressAsUint8_t: %s\n", addr);

    Handle = atoi(addr);
    Serial.printf("Handle received:  %i\n", Handle);

    NewOffset ++;
    if (Handle > 9) { NewOffset ++;} //number of digits
    if (Handle > 99) {NewOffset ++;}

    return NewOffset;
}
