#include "pinStrapping.h"
//LED pins


extern uint8_t Lamps[LAMPS]; //A B C D E F
unsigned int period = 50000;
uint64_t pastTime = 0;


void setLampPins() {
  for (int i = 0; i < LAMPS; i++) {
    pinMode(Lamps[i], OUTPUT);
    digitalWrite(Lamps[i], LOW);
  }

  for (int i = 0; i < LAMPS; i++) {
    digitalWrite(Lamps[i], HIGH);
  }



}

void circleRoll(uint8_t iterations) {
  for (uint8_t e = 0; e < iterations; e++){
    for (uint8_t i = 0; i < LAMPS; i+0 ) {
      unsigned int currentTime = esp_timer_get_time();
      //Serial.println( currentTime - pastTime);
      if(currentTime - pastTime > period) {
        pastTime = currentTime;
        digitalWrite(Lamps[i], LOW);
        int h = i-1;
        if (h < 0) h = 5;
          digitalWrite(Lamps[h], HIGH);
        i++;
      }
    }
  }
  for (int i = 0; i < LAMPS; i++) {
    digitalWrite(Lamps[i], LOW);
  }
}

void toggleLamp(uint8_t lamp, bool onOff) {
  if(onOff)
  digitalWrite(Lamps[lamp], HIGH);
  else if(!onOff)
  digitalWrite(Lamps[lamp], LOW);
}

void doubleblink() {
  uint64_t currentTime = esp_timer_get_time();
  //Serial.println( currentTime - pastTime);
  while(esp_timer_get_time() < currentTime + period) {
    pastTime = currentTime;
    for (uint8_t i = 0; i <LAMPS; i++) {
      digitalWrite(Lamps[i], HIGH);
    }
  }
  currentTime = esp_timer_get_time();

  while(esp_timer_get_time() < currentTime + period) {
    pastTime = currentTime;
    for (uint8_t i = 0; i <LAMPS; i++) {
      digitalWrite(Lamps[i], LOW);
    }
  }
  currentTime = esp_timer_get_time();

  while(esp_timer_get_time() < currentTime + period) {
    pastTime = currentTime;
    for (uint8_t i = 0; i <LAMPS; i++) {
      digitalWrite(Lamps[i], HIGH);
    }
  }
  currentTime = esp_timer_get_time();

  while(esp_timer_get_time() < currentTime + period) {
    pastTime = currentTime;
    for (uint8_t i = 0; i <LAMPS; i++) {
      digitalWrite(Lamps[i], LOW);
    }
  }
}
