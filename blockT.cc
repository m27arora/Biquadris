#include "blockT.h"
#include <vector>

using namespace std;

BlockT::BlockT(): Block{EBlock::T} {
  std::vector<Position> initialPositions;
  Position left = {0, 2};
  initialPositions.emplace_back(left);
  Position midTop = {1, 2};
  initialPositions.emplace_back(midTop);
  Position midBottom = {1, 3};
  initialPositions.emplace_back(midBottom);
  Position right = {2, 2};
  initialPositions.emplace_back(right);
  setPositions(initialPositions);
}

BlockT::~BlockT() {};
