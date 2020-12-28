#include "blockL.h"
#include <vector>

using namespace std;

BlockL::BlockL(): Block{EBlock::L} {
  std::vector<Position> initialPositions;
  Position left = {0, 3};
  initialPositions.emplace_back(left);
  Position middle = {1, 3};
  initialPositions.emplace_back(middle);
  Position bottomRight = {2, 3};
  initialPositions.emplace_back(bottomRight);
  Position topRight = {2, 2};
  initialPositions.emplace_back(topRight);
  setPositions(initialPositions);
}

BlockL::~BlockL() {};
