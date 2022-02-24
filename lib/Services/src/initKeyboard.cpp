//
// Created by Kenneth Dow on 23/2/22.
//

#include "keypad_adapter.h"

KeyboardHardware keypad_adapter::createKeyboardDefinition() {

    static const uint8_t rows =1;
    static const uint8_t columns = 5;

    static const char keyCharacterMap[rows][columns] = {
            {'1', '2', '3', '4', 'A'},
    };

    static byte columnPins[columns] = {13, 12, 14, 27, 26};
    static byte rowPins[rows] = {6};

    return {(char *) keyCharacterMap, rowPins, columnPins, rows, columns};
}