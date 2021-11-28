#include "VoicePatternData.h"


void VoicePatternData::setAt(uint8_t value, uint8_t position) {
    _voicePattern.at(position) = value;
    _triggerPattern.at(position) = true;
}

uint8_t VoicePatternData::returnAt(uint8_t position) {
    if (_triggerPattern.at(position)) {
        return _voicePattern.at(position);
    }
    return 0;
}

void VoicePatternData::setSize(uint8_t newLength) {
    _voicePattern.resize(newLength);
    _triggerPattern.resize(newLength);
}

uint8_t VoicePatternData::getSize() {
    return _voicePattern.size();
}

void VoicePatternData::muteAt(uint8_t position, bool status) {
    _triggerPattern.at(position) = false;
}


