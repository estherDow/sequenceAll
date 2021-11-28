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
    _udp = new WiFiUDP();
    _udp->begin(LOCAL_UDP_PORT);
    //_oscService = new OscService();
    //_oscService->begin(_udp);
}

void SequenceAll::run() {
    _clock->timer();
    _wifiService->handleWifiMode();
    _oscService->receive();
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