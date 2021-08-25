#ifndef Clock_H
#define Clock_H

#include <list>
#include "IObserver.h"
#include "Subject.h"
#include <Arduino.h>
#include <macros.h>


//class Clock : public ISubject{
class Clock : public Subject{

public:
  Clock() {
    //set message to 1 to be understood as clock pulse.
    _msg = 1;
    sender = 'c';
  };
  //Setter functions
  void setBeatsPerMinute(uint16_t beats);

  void timer();
private:
  //Clock setting in BPM
  uint16_t _beats = 120;

  //deltaT in Microseconds = 6e7/(time * steps) uint16_t was too small to hold large value
  int _deltaTime;
  //Subdivisions of each beat defaults to 4 -> Clock multiplier functionality
  uint8_t _steps = 4;
  //Timer Variable in microseconds
  unsigned long _pastState;
  //Settings
//  std::list<IObserver *> list_observer_;
};
#endif
