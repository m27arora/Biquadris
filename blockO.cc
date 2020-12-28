#include "blockO.h"
#include <vector>

using namespace std;

BlockO::BlockO(): Block{EBlock::O} {
  std::vector<Position> initialPositions;
  Position bottomLeft = {0, 3};
  initialPositions.emplace_back(bottomLeft);
  Position topLeft = {0, 2};
  initialPositions.emplace_back(topLeft);
  Position bottomRight = {1, 3};
  initialPositions.emplace_back(bottomRight);
  Position topRight = {1, 2};
  initialPositions.emplace_back(topRight);
  setPositions(initialPositions);
}

BlockO::~BlockO() {};
