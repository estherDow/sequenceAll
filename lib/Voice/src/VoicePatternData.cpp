#include "VoicePatternData.h"


void VoicePatternData::setAt(uint8_t value, uint8_t position) {
    _voicePattern.at(position) = value;
    Serial.printf("VoicePattern received step at: %i, with value %i\n", position, _voicePattern.at(position));
    if (!_triggerPattern.at(position)) {
        _triggerPattern.flip();
    }
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
    std::fill(_triggerPattern.begin(), _triggerPattern.end(), false);
}

uint8_t VoicePatternData::getSize() {
    return _voicePattern.size();
}

void VoicePatternData::muteAt(uint8_t position) {
    _triggerPattern.flip();
}

void VoicePatternData::deleteAt(uint8_t position) {
    if (_triggerPattern.at(position)) {
        _triggerPattern.flip();
    }
    _voicePattern.at(position) = 0;
}


