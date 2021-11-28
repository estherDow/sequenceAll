#include "Module.h"


//Patch something to the Clock
void Module::attach(Module *module) {
    this->list_observer_.push_back(module);
}

//Unpatch something from the Clock
void Module::detach(Module *module) {
    this->list_observer_.remove(module);
}

//Send one to many
void Module::notify(OSCMessage & message) {
    auto iterator = list_observer_.begin();
    while (iterator != list_observer_.end()) {
        (*iterator)->update(message);
        ++iterator;
    }
}

//Send one to one

bool Module::dispatch(void *context, const char * pattern, void (*callback)( void *context, OSCMessage &), int addr_offset){
    if (fullMatch(pattern, addr_offset)){
        callback(context,*this);
        return true;
    } else {
        return false;
    }
}

bool Module::route(void *context, const char * pattern, void (*callback)( void *context, OSCMessage &, uint8_t), int initial_offset){
    int match_offset = match(pattern, initial_offset);
    if (match_offset>0){
        callback(context, *this, match_offset + initial_offset);
        return true;
    } else {
        return false;
    }
}








