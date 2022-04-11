//
// Created by Kenneth Dow on 10/4/22.
//

#include "SequenceAllBuilder.h"

SequenceAllBuilder &SequenceAllBuilder::setClock(uint16_t beatsPerMinute) {
    sequenceAllProperties.cClock = new Clock();
    sequenceAllProperties.cClock->begin(beatsPerMinute);

    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setVoices(uint8_t numberOfVoices = 2, uint8_t sequenceLength = 16) {
    sequenceAllProperties.voiceContainer = new VoiceContainer(numberOfVoices, sequenceLength);
    Serial.println("Voice Setup Complete");

    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setWifi(const char *ssid, const char *password, WifiMode mode) {
    sequenceAllProperties.wiFiService = new WiFiService();
    WifiErrorCode wifiError = sequenceAllProperties.wiFiService->begin(ssid, password, mode);
    if (wifiError != INIT_WIFI_SERVICE_SUCCESS) {
        Serial.println("Could not initiate Wifi Services");
        Serial.println(wifiError);
    }

    return *this;
}

SequenceAllBuilder &SequenceAllBuilder::setOSCService() {
    sequenceAllProperties.oscService = new OscService(sequenceAllProperties.wiFiService);

    return *this;
}

SequenceAll SequenceAllBuilder::build() {
    return SequenceAll(sequenceAllProperties);
}
