#include "Voice.h"

Voice::Voice(SignalTypes type, uint8_t length) { //trigger t gate g clock c
  sender = type;
  _sequenceLength = length;
  setSize(length);
  for (uint8_t i = 0; i<length;i++){
    setStep(0,i);
  }
}

void Voice::update(SignalTypes subjectLine, int msg) {
  _pulseCounter ++;
  //Serial.printf("Voice Update was called %i times\n", _pulseCounter);
  if (_pulseCounter == _clockPulsesPerStep) {
    createMsg(getCurrentStepValue());
    notify();
    incrementStep();
    _pulseCounter = 0;
  }

}
SignalTypes Voice::getType() {
  return sender;
}

void Voice::setSize(uint8_t newLength) {
    _sequenceLength = newLength;
    _steps.setSize(newLength);
}

void Voice::setStep(uint8_t value, uint8_t position){
  _steps.setAt(value, position);
}

void Voice::muteStep(uint8_t position){
    _steps.muteAt(position);
}

void Voice::deleteStep(uint8_t position){
  _steps.setAt(position, 0);
  _steps.muteAt(position);
}

uint8_t Voice::getCurrentStepNumber() const {
  if (_currentStep < _sequenceLength) {
    return _currentStep;
  }
  else{
    return -1;
  }
}


int Voice::getCurrentStepValue() {
  if (_currentStep < _sequenceLength) {
    return _steps.returnAt(_currentStep);
  }
  else{
    return -1;
  }
}



//set & get human readable divisor but store ppqn/divisor for easier counting
//Whatever you type it will be rounded to the nearest integer divisor.
//20 will be 24 10 will be 12 etc. this could be improved.
void Voice::setQuarterNoteDivisions(uint8_t subDivisions) {
  if (subDivisions > PULSES_PER_QUARTER_NOTE) {
    subDivisions = PULSES_PER_QUARTER_NOTE;
  }
  //implicit type conversion
  _clockPulsesPerStep = PULSES_PER_QUARTER_NOTE / subDivisions;
}

uint8_t Voice::getQuarterNoteDivisions() {
  return PULSES_PER_QUARTER_NOTE / _clockPulsesPerStep;
}

void Voice::incrementStep() {
  _currentStep +=getMotion();
  if (_currentStep < 0) {
    _currentStep = _sequenceLength - _currentStep;
  }
  else if (_currentStep > _sequenceLength - 1){
      uint8_t remainder = _currentStep - _sequenceLength;
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

uint8_t Voice::getMotion() const {
  int8_t motion;
  if(_motion != 0) {
    motion = _motion;
  } else {
    motion = rand() % _sequenceLength +1;
  }
  return motion;
}
