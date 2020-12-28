#include "blockS.h"
#include <vector>

using namespace std;

BlockS::BlockS(): Block{EBlock::S} {
  std::vector<Position> initialPositions;
  Position bottomLeft = {0, 3};
  initialPositions.emplace_back(bottomLeft);
  Position topLeft = {1, 2};
  initialPositions.emplace_back(topLeft);
  Position bottomRight = {1, 3};
  initialPositions.emplace_back(bottomRight);
  Position topRight = {2, 2};
  initialPositions.emplace_back(topRight);
  setPositions(initialPositions);
}

BlockS::~BlockS() {};
