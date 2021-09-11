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



  void update(char subjectLine, int msg);

  char getType();

  void setStep(uint16_t value, uint8_t position);
  void deleteStep(uint8_t position);

  uint8_t getCurrentStepNumber();
  int getCurrentStepValue();
  void incrementStep();

  void resize(uint8_t newLength);
  void setQuarterNoteDivisions(uint8_t subDivisor);
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
