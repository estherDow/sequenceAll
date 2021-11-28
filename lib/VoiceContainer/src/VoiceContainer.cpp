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

void VoiceContainer::receive(void * context, OSCMessage & message) {
    char addr[32];
    message.getAddress(addr, 1);
    uint8_t Handle = atoi(addr);
    uint8_t offset = 1;
    if (Handle > 9) { offset = 2;}
    Voice * target = &reinterpret_cast<VoiceContainer *>(context)->voiceMap->at(Handle);
    reinterpret_cast<VoiceContainer *>(context)->route(target, "/set", Voice::setStep,offset);
}

Voice * VoiceContainer::_select(int Handle) {
    return &voiceMap->at(Handle);
}

void VoiceContainer::update(OSCMessage & message) {
    for(uint8_t i = 0; i < TOTAL_NUMBER_OF_VOICES; i++){
        auto voice = _select(i);
        voice->update(message);
    }
}

