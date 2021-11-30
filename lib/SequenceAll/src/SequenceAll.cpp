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


    _wifiService = new WiFiService();
    //TODO: Add error handling in case WiFi could not be started.
    _oscService = new OscService(&_wifiService->UDP);
}

void SequenceAll::run() {
    cClock->timer();
    wiFiService->handleWifiMode();
    OscMsgChild msg;
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