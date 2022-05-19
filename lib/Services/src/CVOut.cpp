//
// Created by Kenneth Dow on 19/5/22.
//

#include "CVOut.h"

void CVOut::setPin(uint8_t pin) const {
    ledcAttachPin(pin, PWMChannel);
}

void CVOut::update(OSCMessageInterface &message) {
    if (message.fullMatch(path,0)) {
        ledcWrite(PWMChannel, message.getInt(0));
    }
}
