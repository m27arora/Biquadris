#ifndef LEVEL_H
#define LEVEL_H
#include <cstdlib>
#include "block.h"
#include <string>
#include <fstream>

class Grid;

class Level {
  const int levelNumber;
  std::string fileName;
  int seed;
  protected:
  //int getLevelNumber() const;
  std::string getFileName() const;
  int getSeed() const;
  bool noRandom = false;
  std::ifstream noRandomFile;
  std::string noRandomFileName;
  public:
  int getLevelNumber() const;
  Level(int levelNumber, std::string &file, int seed):
    levelNumber{levelNumber}, fileName{file}, seed{seed} {}
  void updateLevel(Grid *grid);
  void setNoRandom(std::string file2);
  void setRandom();
  virtual Block *newBlock() = 0;
  virtual Level *levelUp(Grid *grid) = 0;     // Responsible for setting level of grid
  virtual Level *levelDown(Grid *grid) = 0;  // Responsible for setting level of grid
  virtual ~Level() = 0;
};

#endif
