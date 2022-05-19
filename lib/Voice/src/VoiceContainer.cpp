//
// Created by Kenneth Dow on 19/5/22.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer(uint8_t numberOfVoices, uint8_t sequenceLength) : numberVoices(numberOfVoices), sequenceLength(sequenceLength) {

    setVoices();
}

void VoiceContainer::add(uint8_t Handle) const {
    Voice voice(sequenceLength, Handle);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::setVoices() const {
    for (int voice = 0; voice <  numberVoices; voice++) {
        add(voice);
    }
}