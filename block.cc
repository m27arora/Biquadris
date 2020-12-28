#include "block.h"
#include <utility>

using namespace std;

Block::~Block() {}

Position Block::getBottomLeft() const {
  return bottomLeft;
}

vector<Position> Block::getPositions() const {
  return vecPartPosition;
}

EBlock Block::getType() const {
  return type;
}

bool Block::getIsSet() const {
  return isSet;
}

void Block::set() {
  isSet = true;
}

void Block::setPositions(std::vector<Position> &newPositions) {
  vecPartPosition.swap(newPositions);
}

void Block::setBottomLeft(Position &newBottomLeft) {
  swap(bottomLeft, newBottomLeft);
}
