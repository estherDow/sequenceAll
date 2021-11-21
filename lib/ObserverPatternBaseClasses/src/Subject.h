#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "IObserver.h"
#include "ISubject.h"
#include <SignalTypes.h>

class Subject : public ISubject{
public:
  void attach(IObserver *observer) override;
  void detach(IObserver *observer)override;
  void notify() override;
  void createMsg(int msg) override;
  std::list<IObserver *> list_observer_;
  int _msg;
  SignalTypes sender;
};

#endif
