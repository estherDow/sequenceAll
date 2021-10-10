#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "IObserver.h"
#include "ISubject.h"
#include <Arduino.h>

class Subject : public ISubject{
public:
  void attach(IObserver *observer);
  void detach(IObserver *observer);
  void notify();
  void createMsg(int msg);
  std::list<IObserver *> list_observer_;
  int _msg;
  char sender;
};

#endif
