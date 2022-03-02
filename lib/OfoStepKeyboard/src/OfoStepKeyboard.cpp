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
        pinMode(rowPins[r],INPUT_PULLUP);
    }
}

//TODO: rows and columns need to be reversed in the hardware info struct.
//This way the lowgoing pulse through the columns can be skipped and rows will be continuously read.
//SW is likely to behave the same, because keys pull down to ground on press. row pins are set to input_pull up.

void OfoStepKeyboard::_storePressedKeyToBitMap() {
    // bitMap stores ALL the keys that are being pressed.
    for (byte c=0; c < sizeKeypad.columns; c++) {

        pinMode(columnPins[c],OUTPUT);
        digitalWrite(columnPins[c], LOW);	// Begin column pulse output.

        _readRows(c);

        // Set pin to high impedance input. Effectively ends column pulse.
        digitalWrite(columnPins[c],HIGH);
        pinMode(columnPins[c],INPUT);
    }
}

void OfoStepKeyboard::_readRows(byte counter) {
    for (byte r=0; r<sizeKeypad.rows; r++) {
        bitWrite(bitMap[r], counter, !digitalRead(rowPins[r]));  // keypress is active low so invert to high.
    }
}

bool OfoStepKeyboard::updateList() {

    bool anyActivity = false;

    _deleteIdleKeys();

    _addNewKeysToList();

    return _hadRecentActivity();
}

void OfoStepKeyboard::_deleteIdleKeys() {
    // Delete any IDLE keys
    for (auto & i : keyPad->key) {
        if (i.kstate==IDLE) {
            i.kchar = NO_KEY;
            i.kcode = -1;
            i.stateChanged = false;
        }
    }
};

void OfoStepKeyboard::_addNewKeysToList() {
    // Add new keys to empty slots in the key list.
    for (byte r=0; r<sizeKeypad.rows; r++) {
        for (byte c=0; c<sizeKeypad.columns; c++) {
            bool button = bitRead(bitMap[r],c);
            char keyChar = keymap[r * sizeKeypad.columns + c];
            int keyCode = r * sizeKeypad.columns + c;
            int idx = keyPad->findInList (keyCode);

            _addKeyIfNotInList(idx, button);
        }
    }
}

void OfoStepKeyboard::_addKeyIfNotInList(int idx, bool button) {
    // Key is already on the list so set its next state.
    if (idx > -1)	{
        keyPad->nextKeyState(idx, button);
    }
    // Key is NOT on the list so add it.
    if ((idx == -1) && button) {
        for (byte i=0; i<LIST_MAX; i++) {
            if (keyPad->key[i].kchar==NO_KEY) {		// Find an empty slot or don't add key to list.
                keyPad->key[i].kchar = keyChar;
                keyPad->key[i].kcode = keyCode;
                keyPad->key[i].kstate = IDLE;		// Keys NOT on the list have an initial state of IDLE.
                keyPad->nextKeyState (i, button);
                break;	// Don't fill all the empty slots with the same key.
            }
        }
    }
}

bool OfoStepKeyboard::_hadRecentActivity() {
    // Report if the user changed the state of any key.
    bool anyActivity = false;
    for (auto & i : keyPad->key) {
        if (i.stateChanged) anyActivity = true;
    }
    return anyActivity;
}

void OfoStepKeyboard::transitionTo(byte idx, KeyState nextState) {
    key[idx].kstate = nextState;
    key[idx].stateChanged = true;

    // Sketch used the getKey() function.
    // Calls keypadEventListener only when the first key in slot 0 changes state.
    if (single_key)  {
        if ( (keypadEventListener!=NULL) && (idx==0) )  {
            keypadEventListener(key[0].kchar);
        }
        //call the event listener that contains the key state, if available
        if ( (keypadStatedEventListener!=NULL) && (idx==0) )
        {
            keypadStatedEventListener(key[0].kchar, nextState);
        }
    }
        // Sketch used the getKeys() function.
        // Calls keypadEventListener on any key that changes state.
    else {
        if (keypadEventListener!=NULL)  {
            keypadEventListener(key[idx].kchar);
        }
        //call the event listener that contains the key state, if available
        if (keypadStatedEventListener!=NULL)
        {
            keypadStatedEventListener(key[idx].kchar, nextState);
        }
    }
}
