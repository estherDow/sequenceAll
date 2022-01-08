//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"

void SequenceAll::begin() {
    Serial.begin(115200);

    voiceContainer = new VoiceContainer();
    _setVoices();

    cClock = new Clock();
    cClock->setBeatsPerMinute();
    cClock->attach(voiceContainer);
    auto *mdns = new ESPmDNSAdapter();
    auto *udp = new WiFiUDP();
    auto *nvs = new NVSService();
    auto *server = new AsyncWebServer(80);
    wiFiService = new WiFiService( *udp, *server, *mdns, *nvs);
    //TODO: Add error handling in case WiFi could not be started.
    oscService = new OscService(wiFiService->getUDP(), (WiFiServiceInterface &) *wiFiService);

    voiceContainer->select(0)->attach(oscService); //TODO: Test if handle is out of bounds

}

void SequenceAll::run() const {
    cClock->timer();
    wiFiService->handleWifiMode();
    OSCMessage message;
    OscMessageAdapter msg(message);
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
    //TODO: HardReset
}


void SequenceAll::_setVoices() const {
    for (int i = 0; i < TOTAL_NUMBER_OF_VOICES; i++) {
        voiceContainer->add(i);
    }
}

SequenceAll sequenceAll;