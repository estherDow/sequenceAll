//
// Created by Kenneth Dow on 21/11/21.
//

#ifndef SEQUENCEALL_VOICECONTAINER_H
#define SEQUENCEALL_VOICECONTAINER_H

#include <unordered_map>
#include <Arduino.h>
#include <Module.h>
#include "../../Voice/src/Voice.h"
#include "macros.h"

typedef std::unordered_map<int, Module> ContainerMap;

class Container : public Module {

public:
    Container();
    void remove(uint8_t Handle);

    Module * select(uint8_t Handle) const;

    void update(OSCMessageInterface &message) override;

    void attach(ModuleInterface* input) override;

    ~Container() override = default;;

private:
    ContainerMap *moduleMap;
    uint8_t  numberVoices = 0;
    uint8_t sequenceLength = 0;


};

#endif //SEQUENCEALL_VOICECONTAINER_H
