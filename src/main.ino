#include <Arduino.h>
#include <Wire.h>
#include <SequenceAll.h>
#include <SequenceAllBuilder.h>
#include <cstdint>



void setup() {

    Serial.begin(115200);

    main();

}


void loop() {
}
//TODO: Consider a message type that is smaller than OSCMessage, which occupies 40 b with adapter.
int main() {
    SequenceAllBuilder sequenceAllBuilder;
    SequenceAll sequenceAll = sequenceAllBuilder
            .setClock(180)
            .setVoices(4, 16)
            .setWifi("sequenceX", "transLiberationNow", MODE_AP)
            .setOSCService()
            .build();

    sequenceAll.connectOutputToInput(
            sequenceAll.properties.getClock(),
            sequenceAll.properties.getVoiceContainer()
            );

    sequenceAll.connectOutputToInput(
            sequenceAll.properties.getVoiceContainer(),
            sequenceAll.properties.getOSC()
            );

    sequenceAll.connectOutputToInput(
            sequenceAll.properties.getOSC(),
            sequenceAll.properties.getVoiceContainer()
            );


    for (;;) {
        sequenceAll.run();
    }
    return 0;
}
