#include <Clock.h>
#include <Arduino.h>

class dummyObserver : public IObserver {
public:
  dummyObserver() {};
  void update(int _msg);

};

void dummyObserver::update(int _msg){
  Serial.println("Received Update:");
  Serial.println(_msg);
}

Clock clocck;

//Correction found here:
//https://stackoverflow.com/questions/2988273/c-pointer-to-objects
dummyObserver *dummy = new dummyObserver();

void setup() {
Serial.begin(115200);
clocck.setBeatsPerMinute(60);
clocck.setStepsPerBeat(1);
clocck.attach(dummy);
}

uint8_t i = 0;

void loop(/* arguments */) {
i++;
clocck.createMsg(i);
clocck.timer();
}
