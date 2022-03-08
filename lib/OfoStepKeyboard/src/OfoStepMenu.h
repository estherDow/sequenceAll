//
// Created by Kenneth Dow on 24/2/22.
//

#ifndef SEQUENCEALL_OFOSTEPMENU_H
#define SEQUENCEALL_OFOSTEPMENU_H
#include "Module.h"
#include "../../../.pio/libdeps/esp32dev/Keypad/src/Key.h"
#include "OscMessageAdapter.h"

#define MAX_OSC_PATH_LENGTH 32

typedef enum {
    VOICE,
    STEP
}MenuLevel;

class OfoStepMenu : public Module {
public:
    MenuLevel menuLevel = STEP;
    uint8_t currentMenuPosition = 1;
    uint8_t currentVoice = 1;
    uint8_t currentStep = 1;
    char path[MAX_OSC_PATH_LENGTH];
    uint8_t numberVoices{};
    uint8_t stepsPerVoice{};

    OfoStepMenu(){};
    void begin(uint8_t numberOfVoices, uint8_t stepsVoice){numberVoices = numberOfVoices; stepsPerVoice = stepsVoice;};
    static void stateEventListener(void *context, uint8_t key, KeyState state);
    void toggleMenuLevel();
    void switchMenuPosition();
    void setCurrentVoice(uint8_t voice);
    void setCurrentStep(uint8_t step);
    void getMessage();
};



#endif //SEQUENCEALL_OFOSTEPMENU_H
