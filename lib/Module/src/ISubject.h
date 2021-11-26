#ifndef ISUBJECT_H
#define ISUBJECT_H


#include <list>
#include <string>
#include "IObserver.h"

class ISubject{
 public:
  virtual ~ISubject()= default;
  virtual void attach(IObserver *observer) = 0;
  virtual void detach(IObserver *observer) = 0;
  virtual void createMsg(int msg) = 0;
  virtual void notify() = 0;
};

#endif
