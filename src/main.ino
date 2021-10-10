#include <Clock.h>
#include <Voice.h>
#include <Arduino.h>

class dummyObserver : public IObserver {
public:
  dummyObserver() {};
  void update(char sender, int _msg);

};



void dummyObserver::update(char _sender, int _msg){
  Serial.println("Received Update:");
  Serial.println(_msg);
  Serial.println("From:");
  Serial.println(_sender);

}

Clock sClock;
Voice *trigger = new Voice('t', 16);
//Correction found here:
//https://stackoverflow.com/questions/2988273/c-pointer-to-objects
dummyObserver *dummy = new dummyObserver();

void setup() {
Serial.begin(115200);
sClock.setBeatsPerMinute(25);
sClock.attach(trigger);
trigger->attach(dummy);
trigger->setQuarterNoteDivisions(20);
Serial.printf("Subdivisions per quarternote: %i\n", trigger->getQuarterNoteDivisions());

trigger->setStep(1,1);
trigger->setStep(1,5);
trigger->setStep(1,9);
trigger->setStep(1,13);

}


void loop(/* arguments */) {
sClock.timer();

}
