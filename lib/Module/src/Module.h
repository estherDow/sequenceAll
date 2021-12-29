#ifndef MODULE_H
#define MODULE_H

#include <list>

#include <ModuleInterface.h>
#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
#include "OSCClientInterface.h"


class Module : public ModuleInterface{
public:

    virtual void update(OSCClientInterface & message) = 0;

    void attach(ModuleInterface *module);

    void detach(ModuleInterface *module);

    void notify(OSCClientInterface & message); //One to many


private:
    std::list<ModuleInterface *> list_observer_;


};

#endif
