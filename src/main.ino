#include <Arduino.h>
#include <Wire.h>
#include <SequenceAll.h>
#include <cstdint>



void setup() {


    main();

}


void loop() {
}

int main() {
    sequenceAll.begin();

    for (;;) {
        sequenceAll.run();
    }
    return 0;
}
