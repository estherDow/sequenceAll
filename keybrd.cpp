#include "keybrd.h"
//Steps
uint8_t currentStep = 0;
uint8_t sequenceMode = 0;
bool voices[16][VCS]; //saves pad states over 16 steps.
bool play = 0;
//potentiometer
uint8_t potPin = 39;
unsigned int potentiometer;

//Pads
extern byte padPins[VCS];
bool padState[2][VCS]; //lampstate

//matrix
//Keyboard Matrix configuration
//Add number of columns and rows

extern byte rowPins_m1[ROWS]; //connect to the row pinouts of the keypad
extern byte colPins_m1[COLS]; //connect to the column pinouts of the keypad

extern char matrix1_1 [ROWS][COLS];


extern char matrix1_2 [ROWS][COLS];
char key;
char returnKey = NULL;

boolean shift = false; //start with base Keys
// Create two new keypads, one is a number pad and the other is a letter pad.
Keypad basePad( makeKeymap(matrix1_1), rowPins_m1, colPins_m1, sizeof(rowPins_m1), sizeof(colPins_m1) );
Keypad shiftPad( makeKeymap(matrix1_2), rowPins_m1, colPins_m1, sizeof(rowPins_m1), sizeof(colPins_m1) );


unsigned long startTime;

void setKeyboardMatrix() {
  basePad.begin(makeKeymap(matrix1_1));
  shiftPad.begin(makeKeymap(matrix1_2));

  basePad.addEventListener(keypadEvent_base);  // Add an event listener.
  basePad.setHoldTime(2000);                   // Default is 1000mS

  shiftPad.addEventListener(keypadEvent_shift);  // Add an event listener.
  shiftPad.setHoldTime(2000);                   // Default is 1000mS
}

void scanMatrix() {
  if (shift) {
    key = shiftPad.getKey();
    }
  else {
    key = basePad.getKey();
  }
}

static byte kpadState;

//Shift events
void keypadEvent_base(KeypadEvent key) {
  //in here when in base mode
  kpadState = basePad.getState();
  swOnState(key);
}

void keypadEvent_shift(KeypadEvent key) {
  //in here when in shift mode
  kpadState = shiftPad.getState();
  swOnState(key);
}

void swOnState(char key) {

  switch (kpadState) {

    case PRESSED:
    if (key == 'a') {
      currentStep++;
      if (currentStep > 15) currentStep = 0;
      Serial.println(currentStep);
    }
    if (key == 'b') {
      currentStep--;
      if (currentStep == 255) currentStep = 15;
      Serial.println(currentStep);
    }
    if (key == 'B') {
      sequenceMode++;
      if (sequenceMode > 3) sequenceMode = 0;
    }
    if (key == 'c') {
      play = !play;
      Serial.println(play);
    }


    returnKey = key;
    Serial.println(returnKey);
    break;

    case HOLD:
    //Serial.println("ishold");
    if (key == '#')  {               // Toggle between keymaps.
      if (shift == true)  {        // We are currently using a keymap with letters
          shift = false;           // Now we want a keymap with numbers.
          doubleblink();
      }
      else  {                      // We are currently using a keymap with numbers
          shift = true;            // Now we want a keymap with letters.
          doubleblink();
      }
    }
    returnKey = NULL;
    break;

    case RELEASED:
    //Serial.println("released");
    returnKey = NULL;
    break;
  }

}

void setPads() {
  for (uint8_t i = 0; i < VCS; i++) {
    pinMode(padPins[i], INPUT_PULLUP);
  }

}

uint8_t getPads(uint8_t i) {
  uint8_t pad = digitalRead(padPins[i]);
  if (pad == 0) {
    return i;
  }
  else {
    return -1;
  }
}

void stateMachine() {
  for (int i = 0; i <VCS; i++) {
    if (getPads(i) == i && !padState[0][i]) {
      padState[0][i] = true;
      if (!shift)
      padState[1][i] = !padState[1][i];
      voices[currentStep][i] = padState[1][i];
    }
    else if (getPads(i) != i) {
      padState[0][i] = false;
    }
    if (!shift) {
      toggleLamp(i, voices[currentStep][i]);
    }
    else if (shift) {
      toggleLamp(i, padState[0][i]);
    }
  }
}


void potRead() {
  unsigned int avg = 0;

      for (uint8_t i = 0; i < 100; i++) {
        avg += analogRead(potPin);
      }
    potentiometer = map (avg/100, 0, 4095, BPM0, BPM100);
  }

bool isPlayed() {
  return play;
}
