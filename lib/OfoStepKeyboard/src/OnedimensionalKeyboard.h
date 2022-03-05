//
// Created by Kenneth Dow on 5/3/22.
//

#ifndef SEQUENCEALL_ONEDIMENSIONALKEYBOARD_H
#define SEQUENCEALL_ONEDIMENSIONALKEYBOARD_H
#include "../Keypad/src/Key.h"
#include "KeyboardInterface.h"
#include <cstdint>
#include <ostream>

#define LIST_MAX 10



class OnedimensionalKeyboard : public KeyboardInterface {
public:
    Key key[LIST_MAX];


    OnedimensionalKeyboard(char *userKeymap, byte *row, uint8_t numKeys);
    bool getKeys() override;
    void setDebounceTime(unsigned int debounce_time) override {debounceTime = debounce_time;};
    void setHoldTime(unsigned int hold_time) override {holdTime = hold_time;};

    void scanKeys();
    bool updateList();
    void deleteIdleKeys();
    void addActiveKeys();
    void nextKeyState(byte idx, boolean button);
    int findInList(int keyCode);
    void transitionTo(byte idx, KeyState nextState);


    void addOOPEventListener(void (*listener)(void *ObjectContext, char, KeyState), void * ObjectContext);

private:
    uint16_t bitMap{};
    uint8_t numKeys;
    unsigned long startTime;
    char *keymap;
    uint8_t *rowPins;
    uint debounceTime;
    uint holdTime;
    unsigned long holdTimer = 0;

    void (*keypadOOPEventListener)(void *, char, KeyState){};

    void *CallbackTargetObjectContext{};
};


#endif //SEQUENCEALL_ONEDIMENSIONALKEYBOARD_H
