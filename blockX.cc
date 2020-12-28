#include "blockX.h"

BlockX::BlockX(): Block{EBlock::X} {
  std::vector<Position> initialPositions {Position{5, 3}};
  setPositions(initialPositions);
}

BlockX::~BlockX() {};
