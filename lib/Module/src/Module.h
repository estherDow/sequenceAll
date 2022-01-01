#ifndef MODULE_H
#define MODULE_H

#include <list>

#include <ModuleInterface.h>
#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"
#include "OSCMessageInterface.h"


class Module : public ModuleInterface{
public:

    void update(OSCMessageInterface & message) override {}

    void attach(ModuleInterface *module) override;

    void detach(ModuleInterface *module) override;

    void notify(OSCMessageInterface & message) override; //One to many


private:
    std::list<ModuleInterface *> list_observer_;


};

#endif
