//
// Created by Kenneth Dow on 10/4/22.
//

#ifndef SEQUENCEALL_SEQUENCEALLPROPERTIES_H
#define SEQUENCEALL_SEQUENCEALLPROPERTIES_H

#include <Clock.h>
#include <WiFiService.h>
#include "../../Voice/src/VoiceContainer.h"
#include "OscService.h"

class SequenceAllProperties {
public:
    WiFiService* getWifi() const {return wiFiService;}
    VoiceContainer* getVoiceContainer() const {return voiceContainer;}
    Clock* getClock() const {return cClock;}
    OscService* getOSC() const {return oscService;}

    Clock *cClock{};
    VoiceContainer *voiceContainer{};
    WiFiService *wiFiService{};
    OscService *oscService{};
};

#endif //SEQUENCEALL_SEQUENCEALLPROPERTIES_H
