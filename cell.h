#ifndef CELL_H
#define CELL_H
#include "state.h"
#include "subject.h"
#include "position.h"

class Cell final: public Subject {
  EBlock block;
  const Position position;    // Each cell will have a fixed position, hence const
  bool isVisible;
  int blockID;
  public:
  Cell(int x, int y): block{EBlock::Empty}, position{x,y}, isVisible{true}, blockID{-1} {}
  EBlock getBlock() const;
  Position getPosition() const;
  bool getVisibility() const;
  void setBlock(const EBlock &b);
  void setVisibility(bool visibility);
  int getBlockID() const;
  void setBlockID(int id);
};
#endif
