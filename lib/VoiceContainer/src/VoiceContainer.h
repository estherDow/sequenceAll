//
// Created by Kenneth Dow on 21/11/21.
//

#ifndef SEQUENCEALL_VOICECONTAINER_H
#define SEQUENCEALL_VOICECONTAINER_H

#include <unordered_map>
#include <Arduino.h>
#include <Module.h>
#include "Voice.h"
#include <SignalTypes.h>

typedef std::unordered_map<int, Voice> VoiceMap;

class VoiceContainer : public Module {

public:
    VoiceContainer();

    void add(int Handle);

    void remove(int Handle);

    Voice *select(int Handle);

    void update(OSCMessage & message) override;

    ~VoiceContainer() {};

private:
    VoiceMap *voiceMap;

};

#endif //SEQUENCEALL_VOICECONTAINER_H
