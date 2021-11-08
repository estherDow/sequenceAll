#ifndef OSCSERVICE_H
#define OSCSERVICE_H
#include "IOInterface.h"
#include <Module.h>

class OscService : public IOInterface, public Module {
public:
  OscService();
  void send();
  

};
#endif
