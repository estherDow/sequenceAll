//
// Created by Kenneth Dow on 24/2/22.
//

#ifndef SEQUENCEALL_OFOSTEPMENU_H
#define SEQUENCEALL_OFOSTEPMENU_H
#include "Module.h"
#include "../../../.pio/libdeps/esp32dev/Keypad/src/Key.h"

typedef enum {
    VOICE,
    STEP
}MenuLevel;


class OfoStepMenu : public Module {
public:
    MenuLevel menuLevel = STEP;
    uint8_t menuPosition = 1;
    uint8_t currentVoice = 1;
    uint8_t currentStep = 1;
    uint8_t numberVoices;
    uint8_t stepsPerVoice;

    OfoStepMenu(uint8_t numberVoices, uint8_t stepsPerVoice): numberVoices(numberVoices), stepsPerVoice(stepsPerVoice)  {};

    static void stateEventListener(void *context, char key, KeyState state);
    void toggleMenuLevel();
    void switchMenuPosition();
    void setCurrentVoice(uint8_t voice);
    void setCurrentStep(uint8_t step);
};



#endif //SEQUENCEALL_OFOSTEPMENU_H
