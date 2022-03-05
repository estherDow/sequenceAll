//
// Created by Kenneth Dow on 5/3/22.
//

#include "OnedimensionalKeyboard.h"

bool OnedimensionalKeyboard::getKeys() {
    bool keyActivity = false;



    if ( (millis()-startTime)>debounceTime ) {
        scanKeys();
        keyActivity = updateList();
        startTime = millis();
    }
        return keyActivity;
}

void OnedimensionalKeyboard::scanKeys() {
    for (uint8_t r=0; r<numKeys; r++) {
        pinMode(rowPins[r],INPUT_PULLUP);
    }

    for (byte r=0; r<numKeys; r++) {
        bitWrite(bitMap, r, !digitalRead(rowPins[r]));  // keypress is active low so invert to high.
    }
}

OnedimensionalKeyboard::OnedimensionalKeyboard(char *userKeymap, uint8_t *row, uint8_t numKeys) : numKeys(numKeys), keymap(userKeymap), rowPins(row), debounceTime(10), holdTime(1000)
{
    setDebounceTime(10);
    setHoldTime(500);

    startTime = 0;
}

bool OnedimensionalKeyboard::updateList() {
    bool anyActivity = false;
    deleteIdleKeys();
    addActiveKeys();

    // Report if the user changed the state of any key.
    for (byte i=0; i<LIST_MAX; i++) {
        if (key[i].stateChanged) anyActivity = true;
    }

    return anyActivity;
}


void OnedimensionalKeyboard::deleteIdleKeys() {
    // Delete any IDLE keys
    for (byte i=0; i<LIST_MAX; i++) {
        if (key[i].kstate==IDLE) {
            key[i].kchar = NO_KEY;
            key[i].kcode = -1;
            key[i].stateChanged = false;
        }
    }
}

void OnedimensionalKeyboard::addActiveKeys() {
    for (byte r=0; r<numKeys; r++) {
        boolean button = bitRead(bitMap,r);
        char keyChar = keymap[r];
        int keyCode = r;
        int idx = findInList (keyCode);
        // Key is already on the list so set its next state.
        if (idx > -1)	{
            nextKeyState(idx, button);
        }
        // Key is NOT on the list so add it.
        if ((idx == -1) && button) {
            for (byte i=0; i<LIST_MAX; i++) {
                if (key[i].kchar==NO_KEY) {		// Find an empty slot or don't add key to list.
                    key[i].kchar = keyChar;
                    key[i].kcode = keyCode;
                    key[i].kstate = IDLE;		// Keys NOT on the list have an initial state of IDLE.
                    nextKeyState (i, button);
                    break;	// Don't fill all the empty slots with the same key.
                }
            }
        }
    }
}


void OnedimensionalKeyboard::nextKeyState(byte idx, boolean button) {

        key[idx].stateChanged = false;

        switch (key[idx].kstate) {
            case IDLE:
                if (button==KEY_CLOSED) {
                    transitionTo (idx, PRESSED);
                    holdTimer = millis(); }		// Get ready for next HOLD state.
                break;
            case PRESSED:
                if ((millis()-holdTimer)>holdTime)	// Waiting for a key HOLD...
                    transitionTo (idx, HOLD);
                else if (button==KEY_OPEN)		// or for a key to be RELEASED.
                    transitionTo (idx, RELEASED);
                break;
            case HOLD:
                if (button==KEY_OPEN)
                    transitionTo(idx, RELEASED);
                break;
            case RELEASED:
                transitionTo (idx, IDLE);
                break;
        }


}

int OnedimensionalKeyboard::findInList(int keyCode) {
    for (byte i=0; i<LIST_MAX; i++) {
        if (key[i].kcode == keyCode) {
            return i;
        }
    }
    return -1;
}

void OnedimensionalKeyboard::transitionTo(byte idx, KeyState nextState) {
    key[idx].kstate = nextState;
    key[idx].stateChanged = true;

    if (keypadOOPEventListener!=nullptr){
        keypadOOPEventListener(CallbackTargetObjectContext,key[idx].kchar, nextState);
    }

}

void OnedimensionalKeyboard::addOOPEventListener(void (*listener)(void *context, char, KeyState), void *ObjectContext) {
    keypadOOPEventListener = listener;
    CallbackTargetObjectContext = ObjectContext;
}
