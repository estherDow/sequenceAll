#include <Arduino.h>
#include <WiFiUdp.h>

#include <Clock.h>
#include <Voice.h>
#include <SignalTypes.h>
#include <macros.h>
#include <WiFiService.h>
#include <OscService.h>
#include "VoiceContainer.h"


class dummyObserver : public IObserver {
public:
    dummyObserver() = default;

    void update(SignalTypes sender, int _msg) override;

};

void dummyObserver::update(SignalTypes _sender, int _msg) {
    Serial.println("Received Update:");
    Serial.println(_msg);
    Serial.println("From:");
    Serial.println(_sender);
}


Clock sClock;
WiFiService wifiService;
OscService oscService;

WiFiUDP Udp;


SignalTypes trigger = TRIGGER;
//Voice *kick = new Voice(trigger, 16);
dummyObserver *dummy = new dummyObserver();


void setup() {
    VoiceContainer voiceContainer;
    voiceContainer.add(8);
    Voice * kick = voiceContainer.select(8);
    kick->attach(dummy);

    Serial.begin(115200);
    sClock.setBeatsPerMinute(25);
    sClock.attach(kick);

    kick->setQuarterNoteDivisions(20);
    Serial.printf("Subdivisions per quarternote: %i\n", kick->getQuarterNoteDivisions());
    kick->setStep(1, 1);
    kick->setStep(1, 5);
    kick->setStep(1, 9);
    kick->setStep(1, 13);

    Udp.begin(LOCAL_UDP_PORT);
    oscService.begin(&Udp);
}


void loop() {
    sClock.timer();
    wifiService.handleWifiMode();
    oscService.receive();
}
