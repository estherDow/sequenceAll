//
// Created by Kenneth Dow on 22/2/22.
//

#ifndef SEQUENCEALL_KEYPAD_ADAPTER_H
#define SEQUENCEALL_KEYPAD_ADAPTER_H
#include "KeyboardInterface.h"
#include <Module.h>
#include <../Keypad_Matrix/Keypad_Matrix.h>
#include "KeyboardHardwareInfo.h"

#include <cstdint>
class keypad_adapter : public KeyboardInterface, public Module {
public:
    explicit keypad_adapter(KeyboardHardware hardware);
    ~keypad_adapter() override= default;;



};


#endif //SEQUENCEALL_KEYPAD_ADAPTER_H
