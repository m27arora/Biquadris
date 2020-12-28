#include "grid.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockT.h"
#include "blockO.h"
#include "blockS.h"
#include "blockZ.h"
#include "levelThree.h"
#include "levelFour.h"

LevelFour::LevelFour(std::string file, int seed):
  Level{4, file, seed}{}

Block *LevelFour::newBlock() {

   Block *block=nullptr;

  if(noRandom){

   char input;
  if (not(noRandomFile >> input)) {
    noRandomFile.close();
    noRandomFile.open(noRandomFileName, std::ifstream::in);
    noRandomFile >> input;
  }
  switch(input) {
    case 'I': block = new BlockI();
              break;
    case 'J': block = new BlockJ();
              break;
    case 'L': block = new BlockL();
              break;
    case 'T': block = new BlockT();
              break;
    case 'O': block = new BlockO();
              break;
    case 'S': block = new BlockS();
              break;
    case 'Z': block = new BlockZ();
              break;

    default:
              throw "Unrecognized block type";
  }
  return block;
  }

  int prob = std::rand() % 9;

  if(prob <= 1) {
    block = new BlockS();
  }
  else if(prob <= 3){
    block = new BlockZ();
  }
  else if(prob == 4) {
    block = new BlockI();
  }
  else if(prob == 5) {
    block = new BlockJ();
  }
  else if(prob == 6) {
    block = new BlockL();
  }
  else if(prob == 7) {
    block = new BlockO();
  }
  else {
    block = new BlockT();
  }

  return block;
}

Level *LevelFour::levelUp(Grid *grid) {
  Level *newLevel = new LevelFour{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

Level *LevelFour::levelDown(Grid *grid) {
  Level *newLevel = new LevelThree{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}


