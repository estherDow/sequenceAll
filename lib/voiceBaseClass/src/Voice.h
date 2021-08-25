#ifndef VOICE_H
#define VOICE_H

#include <IVoice.h>
#include <vector>
#include <Arduino.h>

class Voice : public IVoice {
public:
 Voice(uint8_t length);


private:
  void setStep(uint16_t value, uint8_t position);
  void deleteStep(uint8_t position);
  void resize(uint8_t newLength);
  void setQuarterNoteDivisions(uint8_t subDivisions);

  //TBD
  void incrementStep(int8_t Increment = 1);
  void decrementStep(int8_t Decrement = 1);
  void setMotion();

  std::vector <uint16_t> _steps;
  uint8_t _currentStep;
  uint8_t _subDivisions;
};



#endif
