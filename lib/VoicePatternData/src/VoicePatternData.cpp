#include <VoicePatternData.h>



void VoicePatternData::at(uint8_t value, uint8_t position) {
  _voicePattern.at(position) = value;
}

uint8_t VoicePatternData::at(uint8_t position) {
  return _voicePattern.at(position);
}

void VoicePatternData::resize(uint8_t newLength) {
  _voicePattern.resize(newLength);
}
