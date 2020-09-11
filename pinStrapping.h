#ifndef PINSTRAPPING_H
#define PINSTRAPPING_H
#include <Arduino.h>
#include <stdint.h>


//LED pins
/*
extern uint8_t Q1;
extern uint8_t Q2;
extern uint8_t Q3;
extern uint8_t Q4;
extern uint8_t Q5;
extern uint8_t Q6;
*/
extern uint8_t Lamps[6];

void setLampPins();
void circleRoll(uint8_t iterations);
void doubleblink();
void toggleLamp(uint8_t lamp, bool onOff);
#endif
