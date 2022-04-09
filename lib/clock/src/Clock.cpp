#include "Clock.h"

hw_timer_t * Timer = nullptr;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void Clock::begin() {
    //Initialize extern vars

    timerSemaphore = xSemaphoreCreateBinary();
    // Use 1st timer of 4 (counted from zero).
    // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
    // info).
    Timer = timerBegin(0, 80, true);
    // Attach onTimer function to our timer.
    timerAttachInterrupt(Timer, &onTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(Timer, 1000000, true);
    // Start an alarm
    timerAlarmEnable(Timer);
}

//Time in BPM with max 360 bpm
void Clock::setBeatsPerMinute() {
       //TODO: Set beats per Minute Method
     _beats = 130;
 //   if (_beats == 0) {
 //       _beats = DEFAULT_BEATS_PER_MINUTE;
 //   }

    if (_beats > 360) {
        _beats = 360;
    }

}

void Clock::setBeatsPerMinute(void * context, OSCMessage &message) {
    reinterpret_cast<Clock *>(context)->_beats = message.getInt(0);
}


bool Clock::timer() {
    // If Timer has fired
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
        uint32_t isrCount = 0, isrTime = 0;
        // Read the interrupt count and time
        portENTER_CRITICAL(&timerMux);
        isrCount = isrCounter;
        isrTime = lastIsrAt;
        portEXIT_CRITICAL(&timerMux);
        // Print it
        Serial.printf("onTimer no. %d at %d ms \n", isrCount, isrTime);
        return true;
    }
    return false;
}

void Clock::doNotify() {

    OSCMessage msg("/t");
    OscMessageAdapter message(msg);
    notify(message);
    message.empty();
    //gets larger than next measurement or triggers an immediate rerun of above code.
}

void IRAM_ATTR Clock::onTimer(){
    // Increment the counter and set the time of ISR
    portENTER_CRITICAL_ISR(&timerMux);
    isrCounter++;
    lastIsrAt = millis();
    portEXIT_CRITICAL_ISR(&timerMux);
    // Give a semaphore that we can check in the loop
    xSemaphoreGiveFromISR(timerSemaphore, NULL);
    // It is safe to use digitalRead/Write here if you want to toggle an output
}


