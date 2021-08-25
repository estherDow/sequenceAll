#include "Subject.h"

//Patch something to the Clock
void Subject::attach(IObserver *observer) {
    this->list_observer_.push_back(observer);
}

//Unpatch something from the Clock
void Subject::detach(IObserver *observer) {
  this->list_observer_.remove(observer);
}

//Set value to be sent via the update fuction
void Subject::createMsg(int msg) {
  this->_msg = msg;
}

//Send Clock Signal
void Subject::notify() {
  std::list<IObserver *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->update(sender, _msg);
    ++iterator;
  }
}
