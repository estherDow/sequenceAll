#include "Clock.h"

//Time in BPM with max 360 bpm
void Clock::setBeatsPerMinute(uint16_t beats) {
  if (beats >360) {
    beats = 360;
  }
  _beats = beats;
}



void Clock::timer() {
  //deltaT in Microseconds = 6e7/(time * steps)
  int currentState = micros();

  //reevaluated everytime the function is called to account for updates 60,000,000 us = 60s
  _deltaTime = 60000000 / (_beats * PULSES_PER_QUARTER_NOTE);

  //At the beginning of the program, pastState is always smaller than currentstate
  if (currentState >= _pastState + _deltaTime) {
    notify();
    //gets larger than next measurement or triggers an immediate rerun of above code.
    _pastState += _deltaTime;
  }
}
