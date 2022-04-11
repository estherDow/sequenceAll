//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer(uint8_t numberOfVoices, uint8_t sequenceLength) : numberVoices(numberOfVoices), sequenceLength(sequenceLength) {
    voiceMap = new VoiceMap();
    setVoices();
}

void VoiceContainer::add(uint8_t Handle) const {
    Voice voice(sequenceLength, Handle);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(uint8_t Handle) {

}

Voice * VoiceContainer::select(uint8_t Handle) const {
    if (Handle >= numberVoices) {
        Handle = numberVoices-1;
    }
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OSCMessageInterface & message) {

    for(uint8_t i = 0; i < numberVoices; i++){
        auto voice = select(i);

        voice->update(message);
    }
}

void VoiceContainer::setVoices() const {
        for (int voice = 0; voice <  numberVoices; voice++) {
            add(voice);
        }

}

void VoiceContainer::attach(ModuleInterface *input) {
    size_t totalNumberOfVoices = voiceMap->size();
    for (int voice = 0; voice < totalNumberOfVoices; voice++) {
        select(voice)->attach(input);
    }
}


