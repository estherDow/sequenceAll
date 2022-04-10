//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer() {
    voiceMap = new VoiceMap();
}

void VoiceContainer::add(uint8_t Handle) const {
    Voice voice(DEFAULT_SEQUENCE_LENGTH, Handle);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(uint8_t Handle) {

}

Voice * VoiceContainer::select(int Handle) const {
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

uint8_t VoiceContainer::getVoiceCount() const {
    return voiceMap->size();
}

void VoiceContainer::setVoices(uint8_t totalNumberOfVoices) const {
        for (int voice = 0; voice < totalNumberOfVoices; voice++) {
            add(voice);
            initSteps(voice);
        }

}
//TODO: Outputs attach to voiceContainer's input, inputs get attached directly to voice objects. this causes problems in the way routing method is currently implemented and needs to be unified
void VoiceContainer::attachToVoices(ModuleInterface *input) const {
    size_t totalNumberOfVoices = getVoiceCount();
    for (int voice = 0; voice < totalNumberOfVoices; voice++) {
        select(voice)->attach(input);
    }
}

void VoiceContainer::initSteps(uint8_t voice) const {
    for (int s = 0;s < DEFAULT_SEQUENCE_LENGTH; s++) {
        char stepNumber[3];
        uint8_t stepValue = 255;
        sprintf(stepNumber, "/%d", s + 1);
        OSCMessage message(stepNumber);
        message.add(stepValue);
        OscMessageAdapter msg(message);
        select(voice)->setStep(select(voice),msg, 0);
        select(voice)->muteStep(select(voice),msg, 0);
    }
}
