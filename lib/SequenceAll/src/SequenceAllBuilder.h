//
// Created by Kenneth Dow on 10/4/22.
//

#ifndef SEQUENCEALL_SEQUENCEALLBUILDER_H
#define SEQUENCEALL_SEQUENCEALLBUILDER_H

#include "SequenceAllProperties.h"
#include "SequenceAll.h"
#include <Clock.h>
#include <WiFiService.h>
#include "../../Voice/src/VoiceContainer.h"

class SequenceAllBuilder {
public:
    SequenceAllBuilder& setClock();
    SequenceAllBuilder &setVoices(uint8_t totalNumberOfVoices);
    SequenceAllBuilder& setWifi();
    SequenceAllBuilder& setOSCService();
    SequenceAll build();
private:
    SequenceAllProperties sequenceAllProperties;

};


#endif //SEQUENCEALL_SEQUENCEALLBUILDER_H
