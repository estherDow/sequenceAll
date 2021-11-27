#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <list>
#include <Module.h>

namespace sequenceAll

class Keyboard : public Subject{
public:
  void setPins();
  void scanKeys();
  void setLongPress();

}


#endif
