#include "blockJ.h"
#include <vector>

using namespace std;

BlockJ::BlockJ(): Block{EBlock::J} {
  std::vector<Position> initialPositions;
  Position bottomLeft = {0, 3};
  initialPositions.emplace_back(bottomLeft);
  Position topLeft = {0, 2};
  initialPositions.emplace_back(topLeft);
  Position middle = {1, 3};
  initialPositions.emplace_back(middle);
  Position right = {2, 3};
  initialPositions.emplace_back(right);
  setPositions(initialPositions);
}

BlockJ::~BlockJ() {};
