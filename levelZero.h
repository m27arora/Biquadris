#ifndef LEVELZERO_H
#define LEVELZERO_H
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>
#include <fstream>

class Grid;

class LevelZero final : public Level {
  std::ifstream fileStream;
  public:
  LevelZero(std::string file, int seed);
  Block *newBlock() override;
  Level *levelUp(Grid *grid) override;
  Level *levelDown(Grid *grid) override;
};

#endif
