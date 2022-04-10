//
// Created by Kenneth Dow on 10/4/22.
//

#ifndef SEQUENCEALL_BUTTON_H
#define SEQUENCEALL_BUTTON_H

#include <cstdint>

class Button {
    Button(uint8_t pin, bool closedState, bool isInterrupt, void * callback);
};


#endif //SEQUENCEALL_BUTTON_H
