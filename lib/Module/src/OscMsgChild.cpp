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
