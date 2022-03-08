//
// Created by Kenneth Dow on 26/11/21.
//

#include "SequenceAll.h"

void SequenceAll::begin() {
    Serial.begin(115200);

    voiceContainer = new VoiceContainer();
    _setVoices();
    Serial.println("Voice Setup Complete");

    cClock = new Clock();
    cClock->setBeatsPerMinute();
    cClock->attach(voiceContainer);

    menu = new OfoStepMenu();
    menu->begin(TOTAL_NUMBER_OF_VOICES,DEFAULT_SEQUENCE_LENGTH);
    OfoStepKeyboardDefinition = new initKeyboard();
    keyBoard = new OnedimensionalKeyboard((char*)OfoStepKeyboardDefinition->keyCharacterMap,OfoStepKeyboardDefinition->rowPins, OfoStepKeyboardDefinition->numberKeys);
    keyBoard->addOOPEventListener(OfoStepMenu::stateEventListener, menu);

    //TODO: Move this into constructor of WifiService.
    auto *mdns = new ESPmDNSAdapter();
    auto *udp = new WiFiUDP();
    auto *server = new AsyncWebServer(80);

    wiFiService = new WiFiService(udp, server, mdns);
    WifiErrorCode wifiError = wiFiService->begin();
    if (wifiError != INIT_WIFI_SERVICE_SUCCESS) {
        Serial.println("Could not initiate Wifi Services");
        Serial.println(wifiError);
    }

    //TODO: Inform user, Parameters of WiFi are not set.

    oscService = new OscService((WiFiServiceInterface &) *wiFiService);

    _attachVoices();
}

void SequenceAll::run() const {
    //TODO: Have this in a separate, more accessible Place
    cClock->timer();

    RecipientAddress voiceContainerAddress(
            voiceContainer,
            "/voice",
            VoiceContainer::receive,
            0
    );

    RecipientAddress remoteIPAddress(
            oscService,
            "/addMe",
            OscService::addRemoteIP,
            0
    );

    OSCMessage message("/needed.dont.ask");
    OscMessageAdapter msg(message);

    if (keyBoard->getKeys()) {
        menu->getMessage(msg);
    }
    else if (oscService->receive(msg)) {
        _oscMessageReceiveDebug(msg);
    }
    msg.route(voiceContainerAddress);
    msg.route(remoteIPAddress);
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

void SequenceAll::_attachVoices() const {
    for (int i = 0; i < TOTAL_NUMBER_OF_VOICES; i++) {
        voiceContainer->select(i)->attach(oscService);
        for (int s = 0;s < DEFAULT_SEQUENCE_LENGTH; s++) {
            char stepNumber[3];
            uint8_t stepValue = 255;
            sprintf(stepNumber, "/%d", s + 1);
            OSCMessage message(stepNumber);
            message.add(stepValue);
            OscMessageAdapter msg(message);
            voiceContainer->select(i)->setStep(voiceContainer->select(i),msg, 0);
            voiceContainer->select(i)->muteStep(voiceContainer->select(i),msg, 0);
        }
    }
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

SequenceAll sequenceAll;