//
// Created by Kenneth Dow on 23/2/22.
//

#ifndef SEQUENCEALL_OFOSTEPKEYBOARD_H
#define SEQUENCEALL_OFOSTEPKEYBOARD_H
#include <../Keypad/src/Keypad.h>
#include "KeyboardInterface.h"
#include "KeyboardHardwareInfo.h"
#include "keypad_adapter.h"
#include "OfoStepMenu.h"
#include <Key.h>

typedef char KeypadEvent;

class OfoStepKeyboard : public KeyboardInterface, public Module {
public:
    explicit OfoStepKeyboard(KeyboardHardware keyboardHardware);

    static void eventListener(char, KeyState);

    void setDebounceTime(uint8_t) override;

    void setHoldTime(uint8_t) override;

    bool getKeys() override;

    KeyState getState();

private:
    Keypad *keyPad;
    OfoStepMenu *menu;
    void scanKeys();

    bool updateList();



};


#endif //SEQUENCEALL_OFOSTEPKEYBOARD_H
