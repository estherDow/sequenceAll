//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"

void SequenceAll::begin() {
    Serial.begin(115200);
    NVS.begin();

    voiceContainer = new VoiceContainer();
    _setVoices();

    cClock = new Clock();
    cClock->setBeatsPerMinute();
    cClock->attach(voiceContainer);

    wiFiService = new WiFiService();
    //TODO: Add error handling in case WiFi could not be started.
    oscService = new OscService(wiFiService);

    voiceContainer->select(0)->attach(oscService); //TODO: Test if handle is out of bounds

}

void SequenceAll::run() {
    cClock->timer();
    wiFiService->handleWifiMode();
    OSCMessage message;
    OscMsgChild msg(message);
    if (oscService->receive(msg)) {
        if (msg.isInt(0)) {
            Serial.printf("osc message: %i \n", msg.getInt(0));
        }
        if (msg.isString(0)) {
            int length = msg.getDataLength(0);
            char str[length];
            msg.getString(0, str, length);
            Serial.println(str);
        }
        RecipientAddress destinationAddress(
                voiceContainer,
                "/voice",
                VoiceContainer::receive,
                0
                );
        msg.route(destinationAddress);
    }
}

void SequenceAll::save() {
    //TODO:Save current machine State in NVM

}

void SequenceAll::reset() {
    NVS.eraseAll();
}


void SequenceAll::_setVoices() {
    for (int i = 0; i < TOTAL_NUMBER_OF_VOICES; i++) {
        voiceContainer->add(i);
    }
}

SequenceAll sequenceAll;