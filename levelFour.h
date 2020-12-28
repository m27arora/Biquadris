#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include "level.h"
#include <cstdlib>
#include "block.h"
#include <string>

class Grid;

class LevelFour final : public Level {
  const int levelNumber = 4;
  std::ifstream filestream2;
  public:
  LevelFour(std::string file, int seed);
  Block *newBlock() override;
  Level *levelUp(Grid *grid) override;
  Level *levelDown(Grid *grid) override;
};

#endif
