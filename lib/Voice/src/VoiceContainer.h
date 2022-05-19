//
// Created by Kenneth Dow on 19/5/22.
//

#ifndef SEQUENCEALL_VOICECONTAINER_H
#define SEQUENCEALL_VOICECONTAINER_H

#include "../../Containter/src/Container.h"

class VoiceContainer : public Container {

    void setVoices() const;

    void add(uint8_t Handle) const;

};


#endif //SEQUENCEALL_VOICECONTAINER_H
