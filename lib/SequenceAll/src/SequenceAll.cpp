//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"
WiFiService wiFiService;
SequenceAll::SequenceAll() {
    Serial.begin(115200);
    _voiceContainer = new VoiceContainer();
    _setVoices();

    _clock = new Clock();
    _clock->setBeatsPerMinute(DEFAULT_BEATS_PER_MINUTE);
    _clock->attach(_voiceContainer);
    //_wifiService = new WiFiService();
    //_udp = new WiFiUDP();
    //_udp->begin(LOCAL_UDP_PORT);
    //_oscService = new OscService();
    //_oscService->begin(_udp);
}

void SequenceAll::run() {
    _clock->timer();
    //_wifiService->handleWifiMode();
    //_oscService->receive();
}

void SequenceAll::save() {
    //TODO:Save current machine State in NVM
}


void SequenceAll::_setVoices() {
    for (int i = 0; i < TOTAL_NUMBER_OF_VOICES; i++) {
        _voiceContainer->add(i);
    }
}