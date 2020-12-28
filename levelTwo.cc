#include "grid.h"
#include "levelOne.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockT.h"
#include "blockO.h"
#include "blockS.h"
#include "blockZ.h"
#include "levelTwo.h"
#include "levelThree.h"

LevelTwo::LevelTwo(std::string file, int seed):
  Level{2, file, seed}{}

Block *LevelTwo::newBlock() {

  Block *block = nullptr;
  int prob = std::rand() % 7;

  if(prob == 0) {
    block = new BlockS();
  }
  else if(prob == 1){
    block = new BlockZ();
  }
  else if(prob == 2) {
    block = new BlockI();
  }
  else if(prob == 3) {
    block = new BlockJ();
  }
  else if(prob == 4) {
    block = new BlockL();
  }
  else if(prob == 5) {
    block = new BlockO();
  }
  else {
    block = new BlockT();
  }

  return block;
}

Level *LevelTwo::levelUp(Grid *grid) {
  Level *newLevel = new LevelThree{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

Level *LevelTwo::levelDown(Grid *grid) {
  Level *newLevel = new LevelOne{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

