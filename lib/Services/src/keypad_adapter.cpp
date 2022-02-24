//
// Created by Kenneth Dow on 22/2/22.
//

#include "keypad_adapter.h"


keypad_adapter::keypad_adapter() {
    KeyboardHardware keyboard = createKeyboardDefinition();

}

void keypad_adapter::defineEventListeners(char key) {

    const char *address = "/voice/1" ;

    OSCMessage message;
    OscMessageAdapter msg(message);




}
