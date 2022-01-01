//
// Created by Kenneth Dow on 26/12/21.
//

#ifndef SEQUENCEALL_MODULEINTERFACE_H
#define SEQUENCEALL_MODULEINTERFACE_H

class OSCMessageInterface;

class ModuleInterface {
public:
    virtual ~ModuleInterface() = default;
    virtual void update(OSCMessageInterface & message) = 0;

    virtual void attach(ModuleInterface *module) = 0;

    virtual void detach(ModuleInterface *module) = 0;

    virtual void notify(OSCMessageInterface & message) = 0;
};
#endif //SEQUENCEALL_MODULEINTERFACE_H
