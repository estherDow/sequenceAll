#ifndef MODULE_H
#define MODULE_H

#include <list>

#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
#include "OscMsgChild.h"
#include "../../PatchBay/src/PatchBay.h"


//TODO: This should not inherit rom osc message.

class Module {
public:

    virtual void update(OscMsgChild & message) = 0;

    void attach(Module *module);

    void detach(Module *module);

    void notify(OscMsgChild & message); //One to many


private:
    std::list<Module *> list_observer_;


};

#endif
