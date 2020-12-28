#ifndef LEVELONE_H
#define LEVELONE_H
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>

class Grid;

class LevelOne final : public Level {
  const int levelNumber = 1;
  public:
  LevelOne(std::string file, int seed);
  Block *newBlock() override;
  Level *levelUp(Grid *grid) override;
  Level *levelDown(Grid *grid) override;
};

#endif
