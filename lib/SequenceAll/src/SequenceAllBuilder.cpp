//
// Created by Kenneth Dow on 10/4/22.
//

#include "SequenceAllBuilder.h"

SequenceAllBuilder &SequenceAllBuilder::setClock() {
    sequenceAllProperties.cClock = new Clock();
    sequenceAllProperties.cClock->begin();
    sequenceAllProperties.cClock->InitDefaultBeatsPerMinute();

    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setVoices(uint8_t totalNumberOfVoices = 1) {
    sequenceAllProperties.voiceContainer = new VoiceContainer();
    sequenceAllProperties.voiceContainer->setVoices(totalNumberOfVoices);
    Serial.println("Voice Setup Complete");

    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setWifi() {
    sequenceAllProperties.wiFiService = new WiFiService();
    WifiErrorCode wifiError = sequenceAllProperties.wiFiService->begin();
    if (wifiError != INIT_WIFI_SERVICE_SUCCESS) {
        Serial.println("Could not initiate Wifi Services");
        Serial.println(wifiError);
    }

    //TODO: Inform user, Parameters of WiFi are not set.
    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setOSCService() {
    sequenceAllProperties.oscService = new OscService(sequenceAllProperties.wiFiService);

    return *this;
}

SequenceAll SequenceAllBuilder::build() {
    return SequenceAll(sequenceAllProperties);
}
