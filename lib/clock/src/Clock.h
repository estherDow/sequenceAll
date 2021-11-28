#ifndef Clock_H
#define Clock_H

#include <Arduino.h>
#include "ArduinoNvs.h"

#include <Module.h>
#include <SignalTypes.h>
#include <macros.h>


//class Clock : public ISubject{
class Clock : public Module {

public:
    Clock() {};

    //Setter functions
    void setBeatsPerMinute();
    static void setBeatsPerMinute(void * context, OSCMessage & message);
    void timer();
    void update(OscMsgChild & message) override{};
private:
    //Clock setting in BPM
    uint16_t _beats = 120;

    //deltaT in Microseconds = 6e7/(time * steps) uint16_t was too small to hold large value
    int _deltaTime;

    //Timer Variable in microseconds
    unsigned long _pastState;

};

#endif
