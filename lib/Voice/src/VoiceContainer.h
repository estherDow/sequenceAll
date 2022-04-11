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

    void add(uint8_t Handle) const;

    void remove(uint8_t Handle);

    uint8_t getVoiceCount() const;

    Voice *select(int Handle) const;

    void update(OSCMessageInterface &message) override;

    void setVoices(uint8_t totalNumberOfVoices) const;

    void initSteps (uint8_t voice) const;

    void attach(ModuleInterface* input) override;

    ~VoiceContainer() override = default;;

private:
    VoiceMap *voiceMap;


};

#endif //SEQUENCEALL_VOICECONTAINER_H
