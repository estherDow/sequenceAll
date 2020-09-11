
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define VCS 6 //define number of voices as this magic number was scattered around as the program grew
#define LAMPS 6 //define the number of lamps on your device. software assumes equal count of lamps as of buttons or will produce weird glitches or even throws bugs

#define ROWS 2 //define Rows and columns of a device
#define COLS 2

#define BPM0 30 // lowest beats per minute
#define BPM100 300 //highest beats per minute

bool hasLamps();
#endif
