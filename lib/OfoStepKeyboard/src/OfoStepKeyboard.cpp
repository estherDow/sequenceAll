//
// Created by Kenneth Dow on 23/2/22.
//

#include "OfoStepKeyboard.h"

OfoStepKeyboard::OfoStepKeyboard(KeyboardHardware keyboardHardware) {
    KeyboardHardware keyBoard = keypad_adapter::createKeyboardDefinition();

    sizeKeypad.rows = keyBoard.numberRows;
    sizeKeypad.columns = keyBoard.numberColumns;
    keymap = keyBoard.keyMap;

    menu = new OfoStepMenu(4, 16);
    keyPad = new Keypad(keyBoard.keyMap, keyBoard.rowPins, keyBoard.columnPins, keyBoard.numberRows, keyBoard.numberColumns);
    keyPad->addStatedEventListener(eventListener);
}


void OfoStepKeyboard::eventListener(char key, KeyState state) {
    OfoStepMenu::stateEventListener(menu,key, state);
}

