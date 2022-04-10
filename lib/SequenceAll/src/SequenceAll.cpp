//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"

void SequenceAll::run() const {
    //TODO: Have this in a separate, more accessible Place
    if (properties.cClock->timer()) {
        properties.cClock->doNotify();
    } else {
        properties.oscService->receive();
    }
}

void SequenceAll::save() {
    //TODO:Save current machine State in NVM

}

void SequenceAll::reset() {
    ESP.restart();
}


void SequenceAll::_oscMessageReceiveDebug(OSCMessageInterface &msg) {
    if (msg.isInt(0)) {
        Serial.printf("osc message: %i \n", msg.getInt(0));
    }
    if (msg.isString(0)) {
        int length = msg.getDataLength(0);
        char str[length];
        msg.getString(0, str, length);
        Serial.println(str);
    }
}

void SequenceAll::connectOutputToInput(ModuleInterface *output, ModuleInterface *input) {
    output->attach(input);
}
