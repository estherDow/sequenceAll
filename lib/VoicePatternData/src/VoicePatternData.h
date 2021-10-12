#ifndef VOICEPTTERNDATA
#define VOICEPTTERNDATA

#include <vector>

class VoicePatternData {
public:
  
  void at(uint32_t value, uint8_t position);
  uint32_t at(uint8_t position);
  void resize(uint8_t newLength);
private:
  std::vector<uint32_t> _voicePattern;
};
#endif
