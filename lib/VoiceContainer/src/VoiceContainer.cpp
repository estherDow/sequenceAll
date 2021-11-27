//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer() {
    voiceMap = new VoiceMap();
}

void VoiceContainer::add(int Handle) {
    SignalTypes trigger = TRIGGER;
    Voice voice(trigger, DEFAULT_SEQUENCE_LENGTH);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(int Handle) {

}

Voice * VoiceContainer::select(int Handle) {
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OSCMessage & message) {
    for(uint8_t i = 0; i < TOTAL_NUMBER_OF_VOICES; i++){
        auto voice = select(i);
        voice->update(message);
    }
}

