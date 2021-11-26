//
// Created by Kenneth Dow on 21/11/21.
//

#include "VoiceContainer.h"


VoiceContainer::VoiceContainer() {
    voiceMap = new VoiceMap();
}

void VoiceContainer::add(int Handle) {
    SignalTypes trigger = TRIGGER;
    Voice voice(trigger, 16);
    voiceMap->insert ({Handle, voice});
}

void VoiceContainer::remove(int Handle) {

}

Voice * VoiceContainer::select(int Handle) {
    return &voiceMap->at(8);
}