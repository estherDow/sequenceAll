//
// Created by Kenneth Dow on 23/2/22.
//

#ifndef SEQUENCEALL_OFOSTEPKEYBOARD_H
#define SEQUENCEALL_OFOSTEPKEYBOARD_H
#include <../Keypad/src/Keypad.h>
#include "KeyboardInterface.h"
#include "KeyboardHardwareInfo.h"
#include "keypad_adapter.h"
#include "OfoStepMenu.h"
#include <Key.h>
#include <cstdint>

typedef char KeypadEvent;

class OfoStepKeyboard : public KeyboardInterface, public Module {
public:
    explicit OfoStepKeyboard(KeyboardHardware keyboardHardware);

    static void eventListener(char, KeyState);

    void setDebounceTime(unsigned int debounce_time) override;

    void setHoldTime(unsigned int hold_time) override;

    bool getKeys() override;

private:
    Keypad *keyPad;
    static OfoStepMenu *menu;

    KeypadSize sizeKeypad;
    char *keymap;

    byte *rowPins;
    byte *columnPins;
    uint bitMap[MAPSIZE];	// 10 row x 16 column array of bits. Except Due which has 32 columns.

    unsigned long startTime;
    unsigned int debounceTime;
    unsigned int holdTime;
    unsigned long holdTimer;

    bool single_key;

    void scanKeys();
    void _initRows();
    void _storePressedKeyToBitMap();
    void _readRows(byte c);

    bool updateList();
    void _deleteIdleKeys();
    void _addNewKeysToList();
    void _addKeyIfNotInList(int idx, bool button);
    bool _hadRecentActivity();

    void transitionTo(byte idx, KeyState nextState);


};


#endif //SEQUENCEALL_OFOSTEPKEYBOARD_H
