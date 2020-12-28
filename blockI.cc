#include "blockI.h"
#include <vector>

using namespace std;

BlockI::BlockI(): Block{EBlock::I} {
  std::vector<Position> initialPositions;
  Position left = {0, 3};
  initialPositions.emplace_back(left);
  Position midLeft = {1, 3};
  initialPositions.emplace_back(midLeft);
  Position midRight = {2, 3};
  initialPositions.emplace_back(midRight);
  Position right = {3, 3};
  initialPositions.emplace_back(right);
  setPositions(initialPositions);
}

BlockI::~BlockI() {};
