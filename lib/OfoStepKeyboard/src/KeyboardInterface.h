//
// Created by Kenneth Dow on 23/2/22.
//

#ifndef SEQUENCEALL_KEYBOARDINTERFACE_H
#define SEQUENCEALL_KEYBOARDINTERFACE_H
#include <cstdint>
class KeyboardInterface {
public:
    ~KeyboardInterface()=default;
    virtual bool getKeys() = 0;
    virtual void setDebounceTime(uint8_t) = 0;
    virtual void setHoldTime(uint8_t) = 0;

};
#endif //SEQUENCEALL_KEYBOARDINTERFACE_H
