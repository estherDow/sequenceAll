#include "Voice.h"

Voice::Voice(uint8_t length){
  resize(length);
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

//Decide where to define if Case step = 0 here
//or convert when reading from vector.
void Voice::incrementStep(int8_t Increment) {
  if (_currentStep < 0) {
    _currentStep = _steps.size() - _currentStep;
  }
  if (_currentStep > _steps.size()){
      uint8_t remainder = _currentStep - _steps.size();
      _currentStep = remainder;
  }
  _currentStep +=Increment;

}

void Voice::decrementStep(int8_t Decrement) {
  incrementStep(Decrement);
}
