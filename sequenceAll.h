#ifndef SEQUENCEALL_H
#define SEQUENCEALL_H
#include "Arduino.h"
#include "keybrd.h"
#include "pinStrapping.h"
#include "network.h"
#include <stdint.h>

void bpmToUSecs(unsigned int bpm);
void sequenceAll();

void lightBringer();
void loopWorker();
void momento();
#endif
