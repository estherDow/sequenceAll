#include <Clock.h>
#include <Voice.h>
#include <Arduino.h>

#include <VoicePatternData.h>
#include <VoiceDataTypes.h>
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
VoiceDataTypes voiceDatatype = UNSIGNED_16;
VoicePatternData<voiceDatatype> sequence;
VoiceTypes trigger = TRIGGER;
Voice *kick = new Voice(trigger, 16);
//Correction found here:
//https://stackoverflow.com/questions/2988273/c-pointer-to-objects
dummyObserver *dummy = new dummyObserver();

void setup() {
Serial.begin(115200);
sClock.setBeatsPerMinute(25);
sClock.attach(kick);
kick->attach(dummy);
kick->setQuarterNoteDivisions(20);
Serial.printf("Subdivisions per quarternote: %i\n", kick->getQuarterNoteDivisions());

kick->setStep(1,1);
kick->setStep(1,5);
kick->setStep(1,9);
kick->setStep(1,13);

}


void loop(/* arguments */) {
sClock.timer();

}
