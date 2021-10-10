#ifndef VOICEVECTORFACTORY
#define VOICEVECTORFACTORY

#include <VoiceDataTypes.h>
#include <vector>

class VoiceVectorFactory {

  void at(uint8_t entryPosition, uint8_t valueAtStep);
  void resize(uint8_t newSize);
private:
  std::vector <uint16_t> _steps;

};
#endif
