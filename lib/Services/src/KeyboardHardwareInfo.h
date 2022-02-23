//
// Created by Kenneth Dow on 23/2/22.
//

#ifndef SEQUENCEALL_KEYBOARDHARDWAREINFO_H
#define SEQUENCEALL_KEYBOARDHARDWAREINFO_H
#include <cstdint>
typedef struct KeyboardHardware {
    const char * keyMap;
    const uint8_t * rowPins;
    const uint8_t * columnPins;
    uint8_t numberRows;
    uint8_t numberColumns;
    bool enablePullups;
    KeyboardHardware(const char * keyMap, const uint8_t * rowPins, const uint8_t *columnPins, uint8_t numberRows, uint8_t numberColumns, bool enablePullups = true
                ) : keyMap(keyMap), rowPins(rowPins), columnPins(columnPins), numberRows(numberRows), numberColumns(numberColumns), enablePullups(enablePullups) {}
    } KeyboardHardware;


#endif //SEQUENCEALL_KEYBOARDHARDWAREINFO_H
