#ifndef MODULE_H
#define MODULE_H

#include <list>

#include "../../../.pio/libdeps/esp32dev/OSC/OSCMessage.h"


class Module : public OSCMessage {
public:

    virtual void update(OSCMessage & message) = 0;

    void attach(Module *module);

    void detach(Module *module);

    void notify(OSCMessage & message); //One to many

    bool dispatch(
            void *context,
            const char *pattern,
            void (*callback)(OSCMessage &, void *context),
            int addr_offset
            );

    bool route(
            void * context,
            const char *pattern,
            void (*callback)(OSCMessage &, int, void *context),
            int initial_offset
            );
private:
    std::list<Module *> list_observer_;


};

#endif
