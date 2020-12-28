#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"

class Cell;

class TextDisplay final: public Observer {
  std::vector<std::vector<char>> gridOneDisplay;
  std::vector<std::vector<char>> gridTwoDisplay;
  int HiScore=0, levelOne=0, levelTwo=0, scoreOne=0, scoreTwo=0, turn =0;
  EBlock nextBlockOne, nextBlockTwo;

  public:
  TextDisplay();
  void notify(Subject &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
