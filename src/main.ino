#include <Arduino.h>
#include <Wire.h>
#include <SequenceAll.h>
#include <keypad_adapter.h>
#include <cstdint>



void setup() {
     uint8_t ROWS = 4;
     uint8_t COLS = 4;

    const char keys[ROWS][COLS] = {
            {'1', '2', '3', 'A'},
            {'4', '5', '6', 'B'},
            {'7', '8', '9', 'C'},
            {'*', '0', '#', 'D'},
    };

    const uint8_t colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
    const uint8_t rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad


    KeyboardHardware keyboard((const char*)keys,rowPins,colPins,ROWS,COLS);

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
