#include "Voice.h"

Voice::Voice(uint8_t length, uint8_t handle) {
    Handle = handle;
    _sequenceLength = length;
    setSize(length);
    initSequence(length);
}

void Voice::update(OscMsgChild &message) {
    _pulseCounter++;
    uint8_t currentStepValue = getCurrentStepValue();
    if (message.fullMatch("/tick", 0) &&
        (_pulseCounter == _clockPulsesPerStep)
        ) {
        char sender[12];
        sprintf(sender, "/voice/%d", Handle);

        OscMsgChild newMessage(sender);
        newMessage.add(currentStepValue);
        notify(newMessage);
        Serial.printf("Voice current step is %i\n", getCurrentStepNumber() );
        Serial.printf("Value is %i\n", currentStepValue);
        //(currentStepValue > 0) &&
        incrementStep();
        _pulseCounter = 0;

    }
}

void Voice::initSequence(uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        _steps.setAt(0, i);
        _steps.muteAt(i, true);
    }

}

void Voice::setStep(void * context, OscMsgChild &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    uint8_t value = message.getInt(0);

    if (position > 0) { position--;}

    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position) &&
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(value)
    ) {
        Serial.printf("Set Step at %i with value %i \n", position, value);
        reinterpret_cast<Voice *>(context)->_steps.setAt(value, position);
        reinterpret_cast<Voice *>(context)->_steps.muteAt(position, false);
    }
    message.empty();
}

void Voice::muteStep(void * context, OscMsgChild &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    bool status = message.getInt(0);

    if (position > 0) { position--;}

    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)
    ) {
        Serial.printf("Toggle Mute Step at %i to status %i \n", position, status);
        reinterpret_cast<Voice *>(context)->_steps.muteAt(position, status);
    }
    message.empty();
}

void Voice::deleteStep(void * context, OscMsgChild &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    if (position > 0) { position--;}
    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)
    ) {
        Serial.printf("Delete Step at %i \n", position);
        reinterpret_cast<Voice *>(context)->_steps.setAt(position, 0);
        reinterpret_cast<Voice *>(context)->_steps.muteAt(position, true);
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


//void Voice::setMotion(char direction) {
//    switch (direction) {
//        case 'f':
//            _motion = 1;
//        case 'b':
//            _motion = -1;
//        case 'r':
//            _motion = 0;
//        default:
//            _motion = 1;
//    }
//}

//uint8_t Voice::getMotion() const {
//    int8_t motion;
//    if (_motion != 0) {
//        motion = _motion;
//    } else {
//        motion = rand() % _sequenceLength + 1;
//    }
//    return motion;
//}
