//
// Created by Kenneth Dow on 23/2/22.
//

#include "OfoStepKeyboard.h"

OfoStepKeyboard::OfoStepKeyboard(KeyboardHardware keyboardHardware) {
    KeyboardHardware keyBoard = keypad_adapter::createKeyboardDefinition();
    menu = new OfoStepMenu(4, 16);
    keyPad = new Keypad(keyBoard.keyMap, keyBoard.rowPins, keyBoard.columnPins, keyBoard.numberRows, keyBoard.numberColumns);
    keyPad->addStatedEventListener(eventListener);
}


void OfoStepKeyboard::eventListener(char key, KeyState state) {
    OfoStepMenu::stateEventListener(menu,key, state);
}

KeyState OfoStepKeyboard::getState() {

    return IDLE;
}

bool OfoStepKeyboard::getKeys() {
    return false;
}

void OfoStepKeyboard::setDebounceTime(uint8_t) {

}

void OfoStepKeyboard::setHoldTime(uint8_t) {

}

void OfoStepKeyboard::scanKeys() {

}

bool OfoStepKeyboard::updateList() {
    return false;
}
