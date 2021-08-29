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

Clock clocck;
Voice *trigger = new Voice('t', 16);
//Correction found here:
//https://stackoverflow.com/questions/2988273/c-pointer-to-objects
dummyObserver *dummy = new dummyObserver();

void setup() {
Serial.begin(115200);
clocck.setBeatsPerMinute(60);
clocck.attach(trigger);
trigger->attach(dummy);
}

uint8_t i = 0;

void loop(/* arguments */) {

clocck.timer();
}
