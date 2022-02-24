//
// Created by Kenneth Dow on 22/2/22.
//

#ifndef SEQUENCEALL_KEYPAD_ADAPTER_H
#define SEQUENCEALL_KEYPAD_ADAPTER_H
#include "KeyboardInterface.h"
#include <Module.h>
#include <../Keypad/src/Keypad.h>
#include "KeyboardHardwareInfo.h"
#include "OscMessageAdapter.h"
#include "OSCMessage.h"
#include "VoiceContainer.h"
#include <cstdint>
class keypad_adapter : public KeyboardInterface, public Module {
public:
    explicit keypad_adapter();
    ~keypad_adapter() override= default;;

    static KeyboardHardware createKeyboardDefinition();

    static void defineEventListeners(char key);


};


#endif //SEQUENCEALL_KEYPAD_ADAPTER_H
