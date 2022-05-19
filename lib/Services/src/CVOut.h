//
// Created by Kenneth Dow on 19/5/22.
//

#ifndef SEQUENCEALL_CVOUT_H
#define SEQUENCEALL_CVOUT_H

#include "CVInterface.h"
#include "OSCMessageInterface.h"

#include "Module.h"
#include "cstdint"

class CVOut : public CVInterface, public Module {
public:
    explicit CVOut(uint32_t PWMFrequency, uint8_t PWMChannel): PWMFrequency(PWMFrequency), PWMChannel(PWMChannel) {};
    void setPin(uint8_t pin) const;

    void update(OSCMessageInterface & message) override;

private:
    uint32_t PWMFrequency;
    uint8_t PWMChannel;
};


#endif //SEQUENCEALL_CVOUT_H
