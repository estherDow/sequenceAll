//
// Created by Kenneth Dow on 10/4/22.
//

#ifndef SEQUENCEALL_SEQUENCEALLBUILDER_H
#define SEQUENCEALL_SEQUENCEALLBUILDER_H

#include "SequenceAllProperties.h"
#include "SequenceAll.h"
#include <Clock.h>
#include <WiFiService.h>
#include "../../Containter/src/Container.h"

class SequenceAllBuilder {
public:
    SequenceAllBuilder &setClock(uint16_t beatsPerMinute);
    SequenceAllBuilder &setVoices(uint8_t numberOfVoices, uint8_t sequenceLength);
    SequenceAllBuilder &setWifi(const char *ssid, const char *password, WifiMode mode);
    SequenceAllBuilder& setOSCService();
    SequenceAllBuilder &setCVOutPin(uint32_t PWMFreq, uint8_t PWMChannel,uint8_t pin);
    SequenceAll build();
private:
    SequenceAllProperties sequenceAllProperties;

};


#endif //SEQUENCEALL_SEQUENCEALLBUILDER_H
