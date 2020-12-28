#include "grid.h"
#include "levelOne.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockT.h"
#include "blockO.h"
#include "blockS.h"
#include "blockZ.h"
#include "levelZero.h"
#include "levelTwo.h"

LevelOne::LevelOne(std::string file, int seed):
  Level{1, file, seed}{}

Block *LevelOne::newBlock() {

  Block *block = nullptr;
  int prob = std::rand() % 12;

  if(prob == 0) {
    block = new BlockS();
  }
  else if(prob==1){
    block = new BlockZ();
  }
  else if(prob <= 3) {
    block = new BlockI();
  }
  else if(prob <=5) {
    block = new BlockJ();
  }
  else if(prob <= 7) {
    block = new BlockL();
  }
  else if(prob <= 9) {
    block = new BlockO();
  }
  else {
    block = new BlockT();
  }

  return block;
}

Level *LevelOne::levelUp(Grid *grid) {
  Level *newLevel = new LevelTwo{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

Level *LevelOne::levelDown(Grid *grid) {
  Level *newLevel = new LevelZero{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

