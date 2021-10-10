#ifndef VOICE_H
#define VOICE_H

#include <IVoice.h>
#include <VoiceTypes.h>
#include <Arduino.h>

#include <vector>
#include <stdlib.h>     /* srand, rand */

class Voice :  public Module, public IVoice{
public:
 Voice(VoiceTypes type, uint8_t length);



  void update(char subjectLine, int msg);

  VoiceTypes getType();

  void setStep(uint16_t value, uint8_t position);
  void deleteStep(uint8_t position);

  uint8_t getCurrentStepNumber();
  int getCurrentStepValue();
  void incrementStep();

  void resize(uint8_t newLength);
  void setQuarterNoteDivisions(uint8_t subDivisions);
  uint8_t getQuarterNoteDivisions();



  void setMotion(char direction); //forward, backward, tbd: random
  uint8_t getMotion();

private:
  //Always initialize values with some default or else you WILL run into undefined behavior.
  std::vector <uint16_t> _steps;
  uint8_t _sequenceLength;
  uint8_t _currentStep = 1;
  uint8_t _clockPulsesPerStep = 12;
  uint16_t _pulseCounter = 0;
  int8_t _motion = 1;
};



#endif
