//
// Created by Kenneth Dow on 23/2/22.
//

#ifndef SEQUENCEALL_KEYBOARDHARDWAREINFO_H
#define SEQUENCEALL_KEYBOARDHARDWAREINFO_H
#include <cstdint>
typedef struct KeyboardHardware {
    char * keyMap;
    byte *rowPins;
    byte * columnPins;
    byte  numberRows;
    byte numberColumns;
    bool enablePullups;
    KeyboardHardware(char * keyMap, byte *rowPins, byte *columnPins, byte numberRows, byte numberColumns, bool enablePullups = true
                ) : keyMap(keyMap), rowPins(rowPins), columnPins(columnPins), numberRows(numberRows), numberColumns(numberColumns), enablePullups(enablePullups) {}
    } KeyboardHardware;


#endif //SEQUENCEALL_KEYBOARDHARDWAREINFO_H