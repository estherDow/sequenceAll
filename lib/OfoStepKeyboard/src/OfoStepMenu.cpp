//
// Created by Kenneth Dow on 24/2/22.
//

#include "OfoStepMenu.h"

void OfoStepMenu::stateEventListener(void *context, uint8_t key, KeyState state) {
    switch (state) {
        case PRESSED:
            Serial.printf("Key %d \n", key);
            if (key == 4) {
                reinterpret_cast<OfoStepMenu *>(context)->switchMenuPosition();
                break;
            } else {
                if (reinterpret_cast<OfoStepMenu *>(context)->menuLevel == VOICE) {

                    reinterpret_cast<OfoStepMenu *>(context)->setCurrentVoice(key);
                    reinterpret_cast<OfoStepMenu *>(context)->toggleMenuLevel();
                    break;

                } else if (reinterpret_cast<OfoStepMenu *>(context)->menuLevel == STEP) {
                    reinterpret_cast<OfoStepMenu *>(context)->setCurrentStep(key);
                    break;
                }
            }
        case IDLE:
            break;
        case HOLD:
            if (key == 4) {
                reinterpret_cast<OfoStepMenu *>(context)->toggleMenuLevel();
            } else {
                break;
            }
        case RELEASED:
            break;
    }
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

 void OfoStepMenu::getMessage(OSCMessageInterface & message) {
    sprintf(path, "/voice/%d/mute/%d", currentVoice, currentStep);
    message.setAddress(path);
}
