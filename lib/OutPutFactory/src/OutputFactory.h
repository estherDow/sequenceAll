#ifndef OUTPUTFACTORY_H
#define OUTPUTFACTORY_H
#include <Arduino.h>
#include "IOutPuts.h"

//return appropriate object depending on hardware presets.
//https://en.wikipedia.org/wiki/Factory_method_pattern
class OutputFactory{
  IOutPuts make(OutPut OutPutType);
};
#endif
