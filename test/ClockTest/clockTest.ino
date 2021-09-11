#include <Clock.h>
#include <Voice.h>
#include <Arduino.h>

class dummyObserver : public IObserver {
public:
  dummyObserver() {};
  void update(char sender, int _msg);

};



void dummyObserver::update(char sender, int _msg){
  Serial.println("Received Update:");
  Serial.println(_msg);
  Serial.println("From:");
  Serial.println(sender);

}

Clock sClock;
Voice *trigger = new Voice('t', 16);
//Correction found here:
//https://stackoverflow.com/questions/2988273/c-pointer-to-objects
dummyObserver *dummy = new dummyObserver();

void setup() {
UNITY_BEGIN();
Serial.begin(115200);
sClock.setBeatsPerMinute(60);
sClock.attach(trigger);
trigger->attach(dummy);
trigger->setStep(1,1);
trigger->setStep(1,5);
trigger->setStep(1,9);
trigger->setStep(1,13);
}

uint8_t i = 0;

void loop(/* arguments */) {
  for (int i= 0; i < 1000; i++) {
    sClock.timer();
  }

}
