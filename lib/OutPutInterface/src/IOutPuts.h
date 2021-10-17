#ifndef IOUTPUTS_H
#define IOUTPUTS_H
#include <macros.h>
#include <IObserver.h>
enum OutPut {
  OSC,
  MIDI,
  CV,
  LED
};


class IOutPuts {
  //virtual IOutput();
public:
  virtual ~IOutPuts(){};
};
#endif
