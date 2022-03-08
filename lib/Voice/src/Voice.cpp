#include "Voice.h"

Voice::Voice(uint8_t length, uint8_t handle) {
    Handle = handle;
    _sequenceLength = length;
    setSize(length);
    initSequence(length);
}

void Voice::update(OSCMessageInterface &message) {
    _pulseCounter++;

    _callNotify(message);
    _updateVoices(message);
}

void Voice::_callNotify(OSCMessageInterface &message) {
    uint8_t currentStepValue = getCurrentStepValue();
    if (message.fullMatch("/tick", 0) &&
        (_pulseCounter == _clockPulsesPerStep)
            ) {
        if (currentStepValue > 0) {
            Serial.printf("Voice::_callNotify: Current Step Value is %d\n", currentStepValue);
            char sender[32];
            sprintf(sender, "/voice/%d/step/%d", Handle, _currentStep);
            OSCMessage msg(sender);
            msg.add(currentStepValue);
            OscMessageAdapter newMessage(msg);
            notify(newMessage);
        }
        incrementStep();
        _pulseCounter = 0;
    }
}

void Voice::_updateVoices(OSCMessageInterface &message) {
    uint8_t initialOffset = message.match("/voice", 0);
    if (initialOffset > 0) {
        uint8_t voiceHandle;
        uint8_t NewOffset = message.getAddressAsUint8_t(voiceHandle, initialOffset);
        if (voiceHandle > 0) {voiceHandle--;}
        if (voiceHandle == Handle) {
            RecipientAddress AddressForSet(
                    this,
                    "/set",
                    Voice::setStep,
                    NewOffset
            );
            message.route(AddressForSet);

            RecipientAddress AddressForDelete(
                    this,
                    "/delete",
                    Voice::deleteStep,
                    NewOffset
            );
            message.route(AddressForDelete);

            RecipientAddress AddressForMute(
                    this,
                    "/mute",
                    Voice::muteStep,
                    NewOffset
            );
            message.route(AddressForMute);
        }
    }
}

void Voice::initSequence(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        _steps.setAt(0, i);
        _steps.muteAt(i);
    }

}

void Voice::setStep(void * context, OSCMessageInterface &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    uint8_t value = message.getInt(0);

    if (position > 0) { position--;}

    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)) {
        Serial.printf("setStep: Set Step at %i with value %i \n", position, value);
        reinterpret_cast<Voice *>(context)->_steps.setAt(value, position);
    }
    message.empty();
}

void Voice::muteStep(void * context, OSCMessageInterface &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);

    if (position > 0) { position--;}

    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)
    ) {
        Serial.printf("MuteStep: Toggle Mute Step at %i \n", position);
        reinterpret_cast<Voice *>(context)->_steps.muteAt(position);
    }
    message.empty();
}

void Voice::deleteStep(void * context, OSCMessageInterface &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    if (position > 0) { position--;}
    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)
    ) {
        Serial.printf("DeleteStep: Delete Step at %i \n", position);
        reinterpret_cast<Voice *>(context)->_steps.deleteAt(position);
    }
    message.empty();
}


uint8_t Voice::getCurrentStepNumber() const {
    if (_currentStep < _sequenceLength) {
        return _currentStep;
    } else {
        return -1;
    }
}


int Voice::getCurrentStepValue() {
        return _steps.returnAt(_currentStep);
}

void Voice::setQuarterNoteDivisions(uint8_t subDivisions) {
    if (subDivisions > PULSES_PER_QUARTER_NOTE) {
        subDivisions = PULSES_PER_QUARTER_NOTE;
    }
    //implicit type conversion
    _clockPulsesPerStep = PULSES_PER_QUARTER_NOTE / subDivisions;
}

uint8_t Voice::getQuarterNoteDivisions() const {
    return PULSES_PER_QUARTER_NOTE / _clockPulsesPerStep;
}

void Voice::incrementStep() {
    _currentStep ++;
    if (_currentStep < 0) {
        _currentStep = _sequenceLength - _currentStep;
    } else if (_currentStep > _sequenceLength - 1) {
        uint8_t remainder = _currentStep - _sequenceLength;
        _currentStep = remainder;
    }
}

void Voice::setSize(uint8_t newLength) {
    _sequenceLength = newLength;
    _steps.setSize(newLength);
}

bool Voice::_isMessageWithinBounds(uint8_t position) const {
    if (0 <= position && position < _sequenceLength) {
        return true;
    }
    return false;
}





