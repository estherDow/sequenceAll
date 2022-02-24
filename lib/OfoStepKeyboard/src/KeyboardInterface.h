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
    virtual void setDebounceTime(unsigned int) = 0;
    virtual void setHoldTime(unsigned int) = 0;

};
#endif //SEQUENCEALL_KEYBOARDINTERFACE_H
