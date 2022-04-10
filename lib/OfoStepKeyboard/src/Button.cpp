//
// Created by Kenneth Dow on 10/4/22.
//

#include "Button.h"

Button::Button(uint8_t pin, bool closedState, bool isInterrupt, void * callback) {
    if (closedState) {
        pinMode(pin, INPUT);
        attachInterrupt(pin, callback, RISING);
    }
    else {
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(pin, callback, FALLING);
    }
}