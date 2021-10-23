#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include <macros.h>
#include <IObserver.h>
enum InOutPut {
  OSC,
  MIDI,
  CV,
  LED
};


class IOInterface {
  //virtual IOutput();
public:
  virtual ~IOInterface(){};
};
#endif
