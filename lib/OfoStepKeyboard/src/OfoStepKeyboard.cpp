//
// Created by Kenneth Dow on 23/2/22.
//

#include "OfoStepKeyboard.h"

OfoStepKeyboard::OfoStepKeyboard(KeyboardHardware keyboardHardware) {
    KeyboardHardware keyBoard = keypad_adapter::createKeyboardDefinition();

    sizeKeypad.rows = keyBoard.numberRows;
    sizeKeypad.columns = keyBoard.numberColumns;

    menu = new OfoStepMenu(4, 16);
    keyPad = new Keypad(keyBoard.keyMap, keyBoard.rowPins, keyBoard.columnPins, keyBoard.numberRows, keyBoard.numberColumns);
    keyPad->addStatedEventListener(eventListener);
}


void OfoStepKeyboard::eventListener(char key, KeyState state) {
    OfoStepMenu::stateEventListener(menu,key, state);
}


bool OfoStepKeyboard::getKeys() {
    bool keyActivity = false;

    // Limit how often the keypad is scanned. This makes the loop() run 10 times as fast.
    if ( (millis()-startTime)>debounceTime ) {
        scanKeys();
        keyActivity = updateList();
        startTime = millis();
    }

    return keyActivity;}

void OfoStepKeyboard::setDebounceTime(unsigned int debounce_time) {
    keyPad->setDebounceTime(debounce_time);
    debounceTime = debounce_time;
}

void OfoStepKeyboard::setHoldTime(unsigned int hold_time) {
    keyPad->setHoldTime(hold_time);
    holdTime = hold_time;
}

void OfoStepKeyboard::scanKeys() {
    _initRows();
    _storePressedKeyToBitMap();


}

void OfoStepKeyboard::_initRows() {
    // Re-intialize the row pins. Allows sharing these pins with other hardware.
    for (byte r=0; r < sizeKeypad.rows; r++) {
        pinMode(keyPad->rowPins[r],INPUT_PULLUP);
    }
}

//TODO: rows and columns need to be reversed in the hardware info struct.
//This way the lowgoing pulse through the columns can be skipped and rows will be continuously read.
//SW is likely to behave the same, because keys pull down to ground on press. row pins are set to input_pull up.

void OfoStepKeyboard::_storePressedKeyToBitMap() {
    // bitMap stores ALL the keys that are being pressed.
    for (byte c=0; c < sizeKeypad.columns; c++) {

        pinMode(keyPad->columnPins[c],OUTPUT);
        digitalWrite(keyPad->columnPins[c], LOW);	// Begin column pulse output.

        _readRows(c);

        // Set pin to high impedance input. Effectively ends column pulse.
        digitalWrite(keyPad->columnPins[c],HIGH);
        pinMode(keyPad->columnPins[c],INPUT);
    }
}

void OfoStepKeyboard::_readRows(byte counter) {
    for (byte r=0; r<sizeKeypad.rows; r++) {
        bitWrite(keyPad->bitMap[r], counter, !digitalRead(keyPad->rowPins[r]));  // keypress is active low so invert to high.
    }
}

bool OfoStepKeyboard::updateList() {
    return false;
}
