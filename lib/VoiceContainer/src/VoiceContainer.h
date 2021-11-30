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

    static void receive(void *context, OscMsgChild &message, uint8_t initialOffset);

    void update(OscMsgChild &message) override;

    ~VoiceContainer() = default;;

private:
    VoiceMap *voiceMap;

    Voice *_select(int Handle);

};

#endif //SEQUENCEALL_VOICECONTAINER_H
