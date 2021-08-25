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


  void setStep(uint16_t value, uint8_t position);
  void deleteStep(uint8_t position);
  void resize(uint8_t newLength);
  void setQuarterNoteDivisions(uint8_t subDivisions);
  int getCurrentStep();

  void incrementStep(uint8_t sequenceLength);
  void setMotion(char direction); //forward, backward, tbd: random
  uint8_t getMotion(uint8_t sequenceLength);

private:
  std::vector <uint16_t> _steps;
  uint8_t _currentStep;
  uint8_t _subDivisions;
  int8_t _motion = 1;
};



#endif
