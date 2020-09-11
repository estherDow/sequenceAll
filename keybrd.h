#ifndef KEYBRD_H
#define KEYBRD_H
#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include "pinStrapping.h"



//Inner Ring, keyboardMatrix
void setKeyboardMatrix();

void scanMatrix();

void keypadEvent_base(KeypadEvent key);
void keypadEvent_shift(KeypadEvent key);

void swOnState(char key);


//Outer Ring Pads
void setPads();
char getPads(uint8_t i);
void stateMachine();

//pot

void potRead();

bool isPlayed();

#endif /* end of include guard: KEYBRD_H */
