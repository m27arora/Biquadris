#include "blockZ.h"
#include <vector>

using namespace std;

BlockZ::BlockZ(): Block{EBlock::Z} {
  std::vector<Position> initialPositions;
  Position bottomLeft = {1, 3};
  initialPositions.emplace_back(bottomLeft);
  Position topLeft = {0, 2};
  initialPositions.emplace_back(topLeft);
  Position bottomRight = {2, 3};
  initialPositions.emplace_back(bottomRight);
  Position topRight = {1, 2};
  initialPositions.emplace_back(topRight);
  setPositions(initialPositions);
}

BlockZ::~BlockZ() {};
