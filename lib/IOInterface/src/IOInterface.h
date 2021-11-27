#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include <macros.h>

enum InOutPut {
  OSC,
  MIDI,
  CV,
  LED
};


class IOInterface {
  //virtual IOutput();
public:
  virtual ~IOInterface()= default;;
};
#endif
