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

void VoiceContainer::receive(void * context, OscMsgChild & message, uint8_t initialOffset) {
    uint8_t Handle=0;
    uint8_t NewOffset = message.getAddressAsUint8_t(Handle, initialOffset);
    if (Handle > 0) { Handle--; }
    if (Handle < TOTAL_NUMBER_OF_VOICES) {
        Serial.println("voiceContainer::Receive was called");
        Voice *target = &reinterpret_cast<VoiceContainer *>(context)->voiceMap->at(Handle);
        message.route(target, "/set", Voice::setStep, NewOffset);
        message.route(target, "/delete", Voice::deleteStep, NewOffset);
        message.route(target, "/mute", Voice::muteStep, NewOffset);
    }
}

Voice * VoiceContainer::select(int Handle) {
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OscMsgChild & message) {
    for(uint8_t i = 0; i < TOTAL_NUMBER_OF_VOICES; i++){
        auto voice = select(i);
        voice->update(message);
    }
}

uint8_t VoiceContainer::getVoiceCount() {
    return voiceMap->size();
}

