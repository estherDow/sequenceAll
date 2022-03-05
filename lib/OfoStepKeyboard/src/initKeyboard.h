//
// Created by Kenneth Dow on 22/2/22.
//

#ifndef SEQUENCEALL_INITKEYBOARD_H
#define SEQUENCEALL_INITKEYBOARD_H
#include "KeyboardInterface.h"
#include <Module.h>
#include "../../../.pio/libdeps/esp32dev/Keypad/src/Keypad.h"
#include "KeyboardHardwareInfo.h"

#include <cstdint>
class initKeyboard {
public:
    static const byte numberKeys =5;

    byte rowPins[numberKeys] {13, 12, 14, 27, 26};

    const char keyCharacterMap[numberKeys] = { '1', '2', '3', '4', 'A' };
};


#endif //SEQUENCEALL_INITKEYBOARD_H
