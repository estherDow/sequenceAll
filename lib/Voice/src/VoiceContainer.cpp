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

void VoiceContainer::receive(void * context, OSCMessageInterface & message, uint8_t initialOffset) {
    uint8_t Handle=0;
    uint8_t NewOffset = message.getAddressAsUint8_t(Handle, initialOffset);
    if (Handle > 0) { Handle--; }
    if (Handle < TOTAL_NUMBER_OF_VOICES) {
        Serial.println("voiceContainer::Receive was called");
        Voice *target = &reinterpret_cast<VoiceContainer *>(context)->voiceMap->at(Handle);

        RecipientAddress AddressForSet(
                target,
                "/set",
                Voice::setStep,
                NewOffset
                );
        message.route(AddressForSet);

        RecipientAddress AddressForDelete(
                target,
                "/delete",
                Voice::deleteStep,
                NewOffset
        );
        message.route(AddressForDelete);

        RecipientAddress AddressForMute(
                target,
                "/mute",
                Voice::muteStep,
                NewOffset
        );
        message.route(AddressForMute);
    }
}

Voice * VoiceContainer::select(int Handle) {
    if (Handle >= voiceMap->size()) {
        Handle = voiceMap->size() -1;
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

