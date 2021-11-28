//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer() {
    voiceMap = new VoiceMap();
}

void VoiceContainer::add(int Handle) {
    Voice voice(DEFAULT_SEQUENCE_LENGTH);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(int Handle) {

}

void VoiceContainer::receive(void * context, OscMsgChild & message, uint8_t initialOffset) {
    uint8_t Handle=0;
    uint8_t NewOffset = message.getAddressAsUint8_t(Handle, initialOffset);
    Voice * target = &reinterpret_cast<VoiceContainer *>(context)->voiceMap->at(Handle);
    message.route(target, "/set", Voice::setStep,NewOffset);
}

Voice * VoiceContainer::_select(int Handle) {
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OscMsgChild & message) {
    for(uint8_t i = 0; i < TOTAL_NUMBER_OF_VOICES; i++){
        auto voice = _select(i);
        voice->update(message);
    }
}

