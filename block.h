#ifndef BLOCK_H
#define BLOCK_H
#include "position.h"
#include <vector>

// Eblock represents the type of block
enum class EBlock {I, J, L, T, O, S, Z, X, Empty};

class Block {
  Position bottomLeft{0,3}; // Position needed to implement rotate
  std::vector<Position> vecPartPosition;
  const EBlock type;
  bool isSet; // True if block cannot be moved (Will be set by Grid::down() most likely)
  
  public:
  Block(EBlock type): type{type}, isSet{false} {}
  Position getBottomLeft() const;
  std::vector<Position> getPositions() const; // Returns the positions of the 4 blocks it is made of
  EBlock getType() const;
  bool getIsSet() const;
  void set();
  void setPositions(std::vector<Position> &newPositions);
  void setBottomLeft(Position &newBottomLeft);
  virtual ~Block() = 0;
};


#endif
