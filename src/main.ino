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

int main() {
    SequenceAllBuilder sequenceAllBuilder;
    SequenceAll sequenceAll = sequenceAllBuilder
            .setClock()
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
