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
    VoiceContainer(uint8_t numberOfVoices, uint8_t sequenceLength);

    void add(uint8_t Handle) const;

    void remove(uint8_t Handle);

    Voice *select(uint8_t Handle) const;

    void update(OSCMessageInterface &message) override;

    void setVoices() const;

    void attach(ModuleInterface* input) override;

    ~VoiceContainer() override = default;;

private:
    VoiceMap *voiceMap;
    uint8_t  numberVoices = 0;
    uint8_t sequenceLength = 0;


};

#endif //SEQUENCEALL_VOICECONTAINER_H
