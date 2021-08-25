#ifndef OBSERVER_H
#define OBSERVER_H
#include <list>
#include <string>

/* Every observer has the function Update, which gets called from Subject whenever a state change therein occurs.
 * what had me confused for at almost a year (lol) was the name "observer" nothing observes here, nothing is observed.
 * It would make much more sense to call it updater, notifier or even "knock, knock" pattern.
 * Because. Again NOTHING OBSERVES.
 */

class IObserver{
 public:
  virtual ~IObserver(){};
  virtual void update(char sender, int msg) = 0;
};
#endif
