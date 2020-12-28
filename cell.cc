#include "cell.h"

EBlock Cell::getBlock() const {
  return block;
}

Position Cell::getPosition() const {
  return position;
}

bool Cell::getVisibility() const {
  return isVisible;
}

void Cell::setBlock(const EBlock &b) {
  block = b;

  // Changes internally with the above line, 
  // But will only notify observers if it is visible with if block below

  if (getVisibility()) {
    setState(State {0, 0, 0, getBlock(), getPosition(), 0, ChangeType::Eblock, EBlock::Empty});
    notifyObservers();
  }
}

void Cell::setVisibility(bool visibility) {
  isVisible = visibility;
  if (isVisible) { 
    setState(State {0, 0, 0, getBlock(), getPosition(), 0, ChangeType::Eblock, EBlock::Empty});
    notifyObservers();
  } else {
    setState(State {0, 0, 0, getBlock(), getPosition(), 0, ChangeType::Blind, EBlock::Empty});
    notifyObservers();
  }

  //  Commented out old code if any bugs occur
  //setState(State {0, 0, 0, getBlock(), getPosition(), 0,
  //                ChangeType::Eblock, EBlock::Empty});
  //notifyObservers();
}

int Cell::getBlockID() const {
  return blockID;
}

void Cell::setBlockID(int id) {
  blockID = id;
}
