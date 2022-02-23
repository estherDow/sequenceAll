//
// Created by Kenneth Dow on 22/2/22.
//

#include "keypad_adapter.h"


keypad_adapter::keypad_adapter() {
    KeyboardHardware keyboard = _createKeyboardDefinition();

    keyPad = new Keypad(keyboard.keyMap, keyboard.rowPins,keyboard.columnPins, keyboard.numberRows, keyboard.numberColumns);
}
