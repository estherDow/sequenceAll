//
// Created by Kenneth Dow on 23/2/22.
//

#include "initKeyboard.h"

KeyboardHardware initKeyboard::createKeyboardDefinition() {

    static const uint8_t rows =5;
    static const uint8_t columns = 1;

    static const char keyCharacterMap[rows][columns] = {
            { '1' },
            { '2' },
            { '3' },
            { '4' },
            { 'A' }
    };

    static uint8_t columnPins[columns] =  {6};
    static uint8_t rowPins[rows] = {13, 12, 14, 27, 26};

    return {(char *) keyCharacterMap, rowPins, columnPins, rows, columns};
}