#include "Clock.h"

//Time in BPM with max 360 bpm
void Clock::setBeatsPerMinute() {
       //TODO: Set beats per Minute Method
     _beats = 130;
 //   if (_beats == 0) {
 //       _beats = DEFAULT_BEATS_PER_MINUTE;
 //   }

    if (_beats > 360) {
        _beats = 360;
    }

}

void Clock::setBeatsPerMinute(void * context, OSCMessage &message) {
    reinterpret_cast<Clock *>(context)->_beats = message.getInt(0);
}


void Clock::timer() {
    //deltaT in Microseconds = 6e7/(time * steps)
    uint currentState = micros();

    //reevaluated everytime the function is called to account for updates 60,000,000 us = 60s
    _deltaTime = 60000000 / (_beats * PULSES_PER_QUARTER_NOTE);

    //TODO: Implement notify
    //At the beginning of the program, pastState is always smaller than currentstate
    if (currentState >= _pastState + _deltaTime) {
        OSCMessage msg("/tick");
        OscMessageAdapter message(msg);
        notify(message);
        //gets larger than next measurement or triggers an immediate rerun of above code.
        _pastState += _deltaTime;
    }
}


