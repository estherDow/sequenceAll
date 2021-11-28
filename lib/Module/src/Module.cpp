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
void Module::notify(OscMsgChild & message) {
    auto iterator = list_observer_.begin();
    while (iterator != list_observer_.end()) {
        (*iterator)->update(message);
        ++iterator;
    }
}









