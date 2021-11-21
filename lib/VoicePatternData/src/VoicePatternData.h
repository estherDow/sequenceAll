#ifndef VOICEPTTERNDATA
#define VOICEPTTERNDATA

#include <vector>

class VoicePatternData {
public:
  
  void at(uint8_t value, uint8_t position);
  uint8_t at(uint8_t position);
  void resize(uint8_t newLength);
private:
  std::vector<uint8_t> _voicePattern;
};
#endif
