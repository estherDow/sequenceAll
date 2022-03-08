//
// Created by Kenneth Dow on 24/2/22.
//

#include "OfoStepMenu.h"

void OfoStepMenu::stateEventListener(void *context, uint8_t key, KeyState state) {
    switch (state) {
        case PRESSED:
            Serial.printf("OFOStepMenu::stateEventListener: Key %d \n", key);
            if (key == 4) {
                reinterpret_cast<OfoStepMenu *>(context)->switchMenuPosition();
                break;
            }
            else{
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
                break;
            }
            else if (key == 1) {
                ESP.restart();
            }
            else {
                break;
            }
        case RELEASED:
            break;
    }
}

void OfoStepMenu::switchMenuPosition() {
    if (menuLevel == VOICE) { menuLevel = STEP; }
    if(currentMenuPosition < numberVoices) {
        currentMenuPosition++;
    }
    else {
        currentMenuPosition = 1;
    }
    Serial.printf("OfoStepMenu::switchMenuPosition: newPosition: %d, number of voices: %d \n", currentMenuPosition, numberVoices);
}

void OfoStepMenu::setCurrentVoice(uint8_t voice) {
    voice++;
    if (voice > numberVoices)
        voice = numberVoices;
    currentVoice = voice;
}


void OfoStepMenu::toggleMenuLevel() {
    if (menuLevel == VOICE) {
        menuLevel = STEP;
        currentStep = 1;
        currentMenuPosition = 1;
    } else {
        menuLevel = VOICE;
    }
}

void OfoStepMenu::setCurrentStep(uint8_t step) {
    uint8_t menuOffset = currentMenuPosition - 1;
    step++;
    Serial.printf("Voice: %d, Step: %d \n", currentVoice, step);
    currentStep = step + (menuOffset*4);
    sprintf(path, "/voice/%d/mute/%d", currentVoice, currentStep);
    Serial.println(path);
}

 void OfoStepMenu::getMessage() {
    if (path[0] != '\0') {
        OSCMessage message("/needed.dont.ask");
        message.setAddress(path);
        OscMessageAdapter msg(message);
        notify(msg);
        path[0] = '\0';
        message.empty();
    }

}
