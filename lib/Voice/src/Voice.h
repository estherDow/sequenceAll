#ifndef VOICE_H
#define VOICE_H

#include <Arduino.h>
#include "VoicePatternData.h"
#include <cstdlib>     /* srand, rand */
#include <Module.h>
#include "macros.h"
#include "OscMessageAdapter.h"
#include <cstdio>

class Voice : public Module {
public:
    uint8_t Handle;

    explicit Voice(uint8_t length, uint8_t handle);

    void update(OSCMessageInterface &message) override;

    void initSequence(uint8_t length);

    static void setStep(void *context, OSCMessageInterface &message, uint8_t offset = 0);

    static void muteStep(void *context, OSCMessageInterface &message, uint8_t offset = 0);

    static void deleteStep(void *context, OSCMessageInterface &message, uint8_t offset = 0);

    uint8_t getCurrentStepNumber() const;

    int getCurrentStepValue();

    void incrementStep();

    void setSize(uint8_t newLength);

    void setQuarterNoteDivisions(uint8_t subDivisions);

    uint8_t getQuarterNoteDivisions() const;

    //void setMotion(char direction); //forward, backward, tbd: random

    //uint8_t getMotion() const;


    //TODO: Implement save to nvs
    //   void save();
    //TODO: Implement destructor
    ~Voice() = default;;
private:
    //Always initialize values with some default or else you WILL run into undefined behavior.
    VoicePatternData _steps;
    uint8_t _sequenceLength;
    uint8_t _currentStep = 1;
    uint8_t _clockPulsesPerStep = 1;
    uint16_t _pulseCounter = 0;
    int8_t _motion = 1;

    void _callNotify(OSCMessageInterface &message);

    void _updateVoices(OSCMessageInterface &message);

    bool _isMessageWithinBounds(uint8_t position) const;
};

#endif
