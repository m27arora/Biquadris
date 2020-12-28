#include "subject.h"

Subject::~Subject() { }

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Subject::setState(State newS) { state = newS; }

State Subject::getState() const { return state; }
