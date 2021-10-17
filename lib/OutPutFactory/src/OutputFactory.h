#ifndef OUTPUTFACTORY_H
#define OUTPUTFACTORY_H
#include <IOutPuts.h>
#include <OscOut.h>

//return appropriate object depending on hardware presets.
//https://en.wikipedia.org/wiki/Factory_method_pattern
class OutputFactory{
public:
  IOutPuts* make(OutPut OutPutType);
};
#endif
