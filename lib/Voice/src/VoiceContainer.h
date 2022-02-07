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
#include "macros.h"

typedef std::unordered_map<int, Voice> VoiceMap;

class VoiceContainer : public Module {

public:
    VoiceContainer();

    void add(uint8_t Handle);

    void remove(uint8_t Handle);

    uint8_t getVoiceCount();

    Voice *select(int Handle);

    static void receive(void *context, OSCMessageInterface &message, uint8_t initialOffset);

    void update(OSCMessageInterface &message) override;

    ~VoiceContainer() = default;;

private:
    VoiceMap *voiceMap;


};

#endif //SEQUENCEALL_VOICECONTAINER_H