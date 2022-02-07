#ifndef VOICE_PATTERN_DATA_H
#define VOICE_PATTERN_DATA_H
#include "Arduino.h"
#include <vector>

class VoicePatternData {
public:

    void setAt(uint8_t value, uint8_t position);

    void muteAt(uint8_t position);

    void deleteAt(uint8_t position);

    uint8_t returnAt(uint8_t position);

    void setSize(uint8_t newLength);

    uint8_t getSize();

private:
    std::vector<uint8_t> _voicePattern;
    std::vector<bool> _triggerPattern;

};

#endif
