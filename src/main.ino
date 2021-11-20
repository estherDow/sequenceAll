#include <Arduino.h>

#include <Clock.h>
#include <Voice.h>
#include <SignalTypes.h>

#include <WiFiService.h>
#include <OscService.h>


class dummyObserver : public IObserver {
public:
  dummyObserver() {};
  void update(SignalTypes sender, int _msg);

};

void dummyObserver::update(SignalTypes _sender, int _msg){
  //Serial.println("Received Update:");
  //Serial.println(_msg);
  //Serial.println("From:");
  //Serial.println(_sender);
}


Clock sClock;
WiFiService wifiService;




SignalTypes trigger = TRIGGER;
Voice *kick = new Voice(trigger, 16);
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

  wifiService.init();
}


void loop() {
  sClock.timer();
  wifiService.handleWifiMode();
}
