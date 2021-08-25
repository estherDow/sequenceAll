#include "Voice.h"

Voice::Voice(char type, uint8_t length){ //trigger t gate g clock c
  sender = type;
  resize(length);
}

void Voice::update(char subjectLine, int msg) {
  createMsg(getCurrentStep());
  notify();
}

void Voice::setStep(uint16_t value, uint8_t position){
  _steps.at(position) = value;
}

void Voice::deleteStep(uint8_t position){
  _steps.at(position) = 0;
}

void Voice::resize(uint8_t newLength){
  _steps.resize(newLength);
}

void Voice::setQuarterNoteDivisions(uint8_t subDivisions) {
  if (subDivisions > PULSES_PER_QUARTER_NOTE) {
    subDivisions = PULSES_PER_QUARTER_NOTE;
  }
  _subDivisions = subDivisions;
}

int Voice::getCurrentStep() {
  int currentStepValue = _steps.at(_currentStep);
  incrementStep(_steps.size());
  return currentStepValue;

}

void Voice::incrementStep(uint8_t sequenceLength) {
  _currentStep +=getMotion(sequenceLength);
  if (_currentStep < 0) {
    _currentStep = sequenceLength - _currentStep;
  }
  else if (_currentStep > sequenceLength){
      uint8_t remainder = _currentStep - sequenceLength;
      _currentStep = remainder;
  }
}

void Voice::setMotion(char direction) {
  switch (direction) {
    case 'f':
    _motion = 1;
    case 'b':
    _motion = -1;
    case 'r':
    _motion = 0;
  }
}

uint8_t Voice::getMotion(uint8_t sequenceLength) {
  int8_t motion;
  if(_motion != 0) {
    motion = _motion;
  } else {
    motion = rand() % sequenceLength +1;
  }
  return motion;
}
