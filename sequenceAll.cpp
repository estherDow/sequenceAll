#include "sequenceAll.h"

uint64_t pTime = 0;
unsigned int pInt;
uint8_t step= 0;
uint8_t lastStep = 0;
uint8_t seqNotes[6] = {24,25,26,27,32,35};
uint8_t momNotes[6] = {24,25,26,27,32,35};
bool msgOn[2][6] = {
  {0,0,0,0,0,0},
  {0,0,0,0,0,0}
}; //[momentary and sequenced]


extern unsigned int potentiometer;
extern bool voices[16][6]; //saves pad states over 16 steps.
extern bool shift;
extern bool padState[2][6];
extern wlan WLAN;

void bpmToUSecs(unsigned int bpm) {
  pInt = 60000000 / (bpm*4); //bpm* steps lol may be customized in future version
  //Serial.println(pInt);
}

void sequenceAll() {
  bpmToUSecs(potentiometer);
    unsigned int cTime = esp_timer_get_time();

    if(cTime - pTime > pInt) {
      pTime = cTime;
      step++;
      if (step> 15) step= 0;
      Serial.println(step);
    }
}

void lightBringer() {

  for (uint8_t e = 0; e <6; e++) {
  //Serial.print(voices[step][e]);
    if (shift) {
      if (padState[0][e]) {
        toggleLamp(e,padState[0][e]);
      }
      else {
        toggleLamp(e,voices[step][e]);
      }
    }
  }
  //Serial.println("");
}

void loopWorker() {
  //send on message once and off message once
  //check padstate[0][e]
  //check voices[i][e]
  if (lastStep != step) {
    for (uint8_t e = 0; e < 6; e++) { //sequenced on
        if (voices[step][e]) {
          WLAN.sendOsc(1,"/sequenced",seqNotes[e]);
        }

        else if (!voices[step][e]){
          WLAN.sendOsc(0,"/sequenced",seqNotes[e]);
        }
    }
    lastStep = step;
  }

}

void momento() {
  if (shift) {
    for (uint8_t e = 0; e < 6; e++) { //sequenced on

      if (padState[0][e] && !msgOn[0][e]) { //message on
        WLAN.sendOsc(1,"/momentary",momNotes[e]);
        msgOn[0][e] = true;
      }

      if (!padState[0][e] && msgOn[0][e] ) {
        WLAN.sendOsc(0,"/momentary",momNotes[e]);
        msgOn[0][e] = false;
      }
   }
  }

}
