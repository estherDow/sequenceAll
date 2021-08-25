#ifndef IVOICE_H
#define IVOICE_H

#include <list>
#include <Arduino.h>
#include <macros.h>
class IVoice {
public:
  virtual ~IVoice(){};
private:
  virtual void setStep(uint16_t value, uint8_t position) = 0;
  virtual void deleteStep(uint8_t position) = 0;
  virtual void setQuarterNoteDivisions(uint8_t subDivisions) = 0;
};

#endif
