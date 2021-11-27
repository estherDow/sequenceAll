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

bool Module::dispatch(void *context, const char * pattern, void (*callback)(OSCMessage &, void *context), int addr_offset){
    if (fullMatch(pattern, addr_offset)){
        callback(*this, context);
        return true;
    } else {
        return false;
    }
}

bool Module::route(void *context, const char * pattern, void (*callback)(OSCMessage &, int, void *context), int initial_offset){
    int match_offset = match(pattern, initial_offset);
    if (match_offset>0){
        callback(*this, match_offset + initial_offset, context);
        return true;
    } else {
        return false;
    }
}








