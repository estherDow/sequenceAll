//
// Created by Kenneth Dow on 22/2/22.
//

#ifndef SEQUENCEALL_INITKEYBOARD_H
#define SEQUENCEALL_INITKEYBOARD_H
#include "KeyboardInterface.h"
#include <Module.h>
#include "../../../.pio/libdeps/esp32dev/Keypad/src/Keypad.h"
#include "KeyboardHardwareInfo.h"
#include "OscMessageAdapter.h"
#include "OSCMessage.h"
#include "VoiceContainer.h"
#include <cstdint>
class initKeyboard {
public:
    static KeyboardHardware createKeyboardDefinition();

};


#endif //SEQUENCEALL_INITKEYBOARD_H
