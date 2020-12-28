#ifndef LEVELTWO_H
#define LEVELTWO_H
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>

class Grid;

class LevelTwo final : public Level {
  const int levelNumber = 2;
  public:
  LevelTwo(std::string file, int seed);
  Block *newBlock() override;
  Level *levelUp(Grid *grid) override;
  Level *levelDown(Grid *grid) override;
};

#endif
