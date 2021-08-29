#ifndef VOICE_H
#define VOICE_H

#include <IVoice.h>
#include <Subject.h>
#include <IObserver.h>
#include <vector>
#include <Arduino.h>
#include <stdlib.h>     /* srand, rand */

class Voice :  public IObserver, public IVoice, public Subject {
public:
 Voice(char type, uint8_t length);


 //TBD
  void update(char subjectLine, int msg);

  char getType();

  void setStep(uint16_t value, uint8_t position);
  void deleteStep(uint8_t position);

  void resize(uint8_t newLength);
  void setQuarterNoteDivisions(uint8_t subDivisions);
  uint8_t getQuarterNoteDivisions();

  uint8_t getCurrentStepNumber();
  int getCurrentStepValue();
  void incrementStep();

  void setMotion(char direction); //forward, backward, tbd: random
  uint8_t getMotion();

private:
  std::vector <uint16_t> _steps;
  uint8_t _sequenceLength;
  uint8_t _currentStep;
  uint8_t _clockPulsesPerStep = 12;
  uint8_t _pulseCounter;
  int8_t _motion = 1;
};



#endif
