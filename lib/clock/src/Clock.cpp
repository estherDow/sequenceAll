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
    InitDefaultBeatsPerMinute();
    // Start an alarm
    timerAlarmEnable(Timer);
}

//Time in BPM with max 360 bpm
void Clock::InitDefaultBeatsPerMinute() {
       //TODO: Set beats per Minute Method
     _beats = DEFAULT_BEATS_PER_MINUTE;
    setBeatsPerMinute(_beats);
}

void Clock::setBeatsPerMinute(void * context, OSCMessage &message) {

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    uint16_t beats = message.getInt(0);
    reinterpret_cast<Clock *>(context)->_beats = beats;
    setBeatsPerMinute(beats);
}


void Clock::setBeatsPerMinute(uint16_t beats) {
    uint64_t minute = SECOND_IN_US * 60;
    uint64_t timerInterval = minute / beats;
    timerAlarmWrite(Timer, timerInterval, true);
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



