//
// Created by Kenneth Dow on 10/4/22.
//

#ifndef SEQUENCEALL_SEQUENCEALLPROPERTIES_H
#define SEQUENCEALL_SEQUENCEALLPROPERTIES_H

#include <unordered_map>
#include <Clock.h>
#include <WiFiService.h>
#include "../../Containter/src/Container.h"
#include "OscService.h"
#include "CVOut.h"

class SequenceAllProperties {
public:
    WiFiService* getWifi() const {return wiFiService;}
    VoiceContainer* getVoiceContainer() const {return voiceContainer;}
    Clock* getClock() const {return cClock;}
    OscService* getOSC() const {return oscService;}
    CVOut getCVPin(uint8_t handle) const {return CVOutPins.at(handle);}
    Clock *cClock{};
    VoiceContainer *voiceContainer{};
    WiFiService *wiFiService{};
    OscService *oscService{};
    std::unordered_map<int, CVOut> CVOutPins;
};

#endif //SEQUENCEALL_SEQUENCEALLPROPERTIES_H
