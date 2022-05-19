//
// Created by Kenneth Dow on 19/5/22.
//

#ifndef SEQUENCEALL_CVINTERFACE_H
#define SEQUENCEALL_CVINTERFACE_H
#include "cstdint"
#include "ModuleInterface.h"
class CVInterface  {
public:
    virtual ~CVInterface() = default;
    virtual void setPin(uint8_t pin) const = 0;
};
#endif //SEQUENCEALL_CVINTERFACE_H
