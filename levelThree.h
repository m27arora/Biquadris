#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>

class Grid;

class LevelThree final : public Level {
  const int levelNumber = 3;
  std::ifstream filestream2;
  public:
  LevelThree(std::string file, int seed);
  Block *newBlock() override;
  Level *levelUp(Grid *grid) override;
  Level *levelDown(Grid *grid) override;
};

#endif
