#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "state.h"
#include "observer.h"

//class Observer;

class Subject {
  std::vector<Observer *> observers;
  State state;
 protected:
  void setState(State newS);
 public:
  virtual ~Subject() = 0;
  void attach(Observer *o);
  void notifyObservers();
  State getState() const;
};

#endif
