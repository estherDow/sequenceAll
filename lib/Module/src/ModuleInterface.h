//
// Created by Kenneth Dow on 26/12/21.
//

#ifndef SEQUENCEALL_MODULEINTERFACE_H
#define SEQUENCEALL_MODULEINTERFACE_H

#include "OSCClientInterface.h"

class ModuleInterface {
public:
    virtual ~ModuleInterface() = default;
    virtual void update(OSCClientInterface & message) = 0;

    virtual void attach(ModuleInterface *module) = 0;

    virtual void detach(ModuleInterface *module) = 0;

    virtual void notify(OSCClientInterface & message) = 0;
};
#endif //SEQUENCEALL_MODULEINTERFACE_H
