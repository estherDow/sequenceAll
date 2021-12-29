#include <Arduino.h>
#include <Wire.h>
#include <SequenceAll.h>



//class dummyObserver : public IObserver {
//public:
//    dummyObserver() = default;

//    void update(SignalTypes sender, int _msg) override;

//};

//void dummyObserver::update(SignalTypes _sender, int _msg) {
//    Serial.println("Received Update:");
//    Serial.println(_msg);
//    Serial.println("From:");
//    Serial.println(_sender);
//}





//Voice *kick = new Voice(trigger, 16);
//dummyObserver *dummy = new dummyObserver();

//SequenceAll sequenceAll;

void setup() {
    sequenceAll.begin();

}


void loop() {
    sequenceAll.run();
}
