//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer() {
    voiceMap = new VoiceMap();
}

void VoiceContainer::add(uint8_t Handle) {
    Voice voice(DEFAULT_SEQUENCE_LENGTH, Handle);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(uint8_t Handle) {

}

Voice * VoiceContainer::select(int Handle) {
    if (Handle >= voiceMap->size()) {
        Handle = TOTAL_NUMBER_OF_VOICES - 1;
    }
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OSCMessageInterface & message) {
    for(uint8_t i = 0; i < TOTAL_NUMBER_OF_VOICES; i++){
        auto voice = select(i);

        voice->update(message);
    }
}

uint8_t VoiceContainer::getVoiceCount() {
    return voiceMap->size();
}

