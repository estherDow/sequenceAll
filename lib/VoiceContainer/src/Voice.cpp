#include "Voice.h"

Voice::Voice(uint8_t length) { //trigger t gate g clock c
    _sequenceLength = length;
    setSize(length);
    initSequence(length);
}

void Voice::update(OscMsgChild &message) {
    _pulseCounter++;
    //Serial.printf("Voice Update was called %i times\n", _pulseCounter);
    //TODO: This does not work accoring to stack trace:reinterpret_cast<const char *>(CLOCK_SIGNAL_HANDLE)
    if (message.fullMatch("/tick", 0)) {
        if (_pulseCounter == _clockPulsesPerStep) {
            //notify();
            incrementStep();
            _pulseCounter = 0;
        }
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
}

void Voice::muteStep(void * context, OscMsgChild &message, uint8_t offset) {
    uint8_t position = 0;
    message.getAddressAsUint8_t(position, offset);
    bool status = message.getBoolean(0);

    if (position > 0) { position--;}

    if (
    reinterpret_cast<Voice *>(context)->_isMessageWithinBounds(position)
    ) {
        Serial.printf("Toggle Mute Step at %i to status %i \n", position, status);
        reinterpret_cast<Voice *>(context)->_steps.muteAt(position, status);
    }
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
}


uint8_t Voice::getCurrentStepNumber() const {
    if (_currentStep < _sequenceLength) {
        return _currentStep;
    } else {
        return -1;
    }
}


int Voice::getCurrentStepValue() {
    if (_currentStep < _sequenceLength) {
        return _steps.returnAt(_currentStep);
    } else {
        return -1;
    }
}


//set & get human-readable divisor but store PPQN/divisor for easier counting
//Whatever you type it will be rounded to the nearest integer divisor.
//20 will be 24 10 will be 12 etc. this could be improved.
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
