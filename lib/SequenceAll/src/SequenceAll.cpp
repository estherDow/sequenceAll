//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"

void SequenceAll::begin() {
    Serial.begin(115200);
    NVS.begin();

    _voiceContainer = new VoiceContainer();
    _setVoices();

    _clock = new Clock();
    _clock->setBeatsPerMinute();
    _clock->attach(_voiceContainer);

    _wifiService = new WiFiService();

    _oscService = new OscService(&_wifiService->UDP);
    //_oscService->begin();
}

void SequenceAll::run() {
    _clock->timer();
    _wifiService->handleWifiMode();
    OscMsgChild msg = _oscService->receive();
    if(msg.isString(0)) {
        int length = msg.getDataLength(0);
        char str[length];
        msg.getString(0, str, length);
        Serial.println(str);
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
        _voiceContainer->add(i);
    }
}

SequenceAll sequenceAll;