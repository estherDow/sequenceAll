//
// Created by Kenneth Dow on 21/11/21.
//

#include "Container.h"



void Container::remove(uint8_t Handle) {

}

Module * Container::select(uint8_t Handle) const {
    if (Handle >= numberVoices) {
        Handle = numberVoices-1;
    }
    return &voiceMap->at(Handle);
}

void Container::update(OSCMessageInterface & message) {

    for(uint8_t i = 0; i < numberVoices; i++){
        auto voice = select(i);

        voice->update(message);
    }
}

void Container::attach(ModuleInterface *input) {
    size_t totalNumberOfVoices = voiceMap->size();
    for (int voice = 0; voice < totalNumberOfVoices; voice++) {
        select(voice)->attach(input);
    }
}

Container::Container() {
    ContainerMap = new ContainerMap();

}


