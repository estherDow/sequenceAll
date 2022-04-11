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
    SequenceAllBuilder &setVoices(uint8_t numberOfVoices, uint8_t sequenceLength);
    SequenceAllBuilder &setWifi(const char *ssid, const char *password, WifiMode mode);
    SequenceAllBuilder& setOSCService();
    SequenceAll build();
private:
    SequenceAllProperties sequenceAllProperties;

};


#endif //SEQUENCEALL_SEQUENCEALLBUILDER_H
