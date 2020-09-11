#ifndef PINSTRAPPING_H
#define PINSTRAPPING_H
#include <Arduino.h>
#include <stdint.h>
#include "config.h"

void setLampPins();
void circleRoll(uint8_t iterations);
void doubleblink();
void toggleLamp(uint8_t lamp, bool onOff);
#endif
