//
// Created by Kenneth Dow on 24/2/22.
//

#include "OfoStepMenu.h"

void OfoStepMenu::stateEventListener(void *context, uint8_t key, KeyState state) {
    switch (state){
        case PRESSED:
            Serial.printf("Key %d \n", key);
            if (key == 4 ) {
                reinterpret_cast<OfoStepMenu *>(context)->switchMenuPosition();
            }
            else {
                if(reinterpret_cast<OfoStepMenu *>(context)->menuLevel == VOICE) {
                    reinterpret_cast<OfoStepMenu *>(context)->setCurrentVoice(key);
                }
                else if (reinterpret_cast<OfoStepMenu *>(context)->menuLevel == STEP) {
                    reinterpret_cast<OfoStepMenu *>(context)->setCurrentStep(key);                }
            }
        case IDLE:
            break;
        case HOLD:
            if (key == 4 ) {
                reinterpret_cast<OfoStepMenu *>(context)->toggleMenuLevel();
            }
            else {
                break;
            }
        case RELEASED:
            break;
    }
    char currentVoiceAsChar[2];
    itoa(reinterpret_cast<OfoStepMenu *>(context)->currentVoice, currentVoiceAsChar, 10);

    char currentStepAsChar[3];
    itoa(reinterpret_cast<OfoStepMenu *>(context)->currentStep, currentStepAsChar, 10);
}

void OfoStepMenu::switchMenuPosition() {
    if( menuPosition < numberVoices) {
        menuPosition++;
    }
    else {
        menuPosition = 1;
    }
}

void OfoStepMenu::setCurrentVoice(uint8_t voice) {
    uint8_t menuOffset = menuPosition - 1;

    currentVoice = voice + menuOffset;
}


void OfoStepMenu::toggleMenuLevel() {
    if (menuLevel == VOICE) {
        menuLevel = STEP;
    } else {
        menuLevel = VOICE;
    }
}

void OfoStepMenu::setCurrentStep(uint8_t step) {
    uint8_t menuOffset = menuPosition - 1;
    Serial.printf("Voice: %d, Step: %d \n", currentVoice, step);
    currentStep = step + menuOffset;
}
