#include "levelZero.h"
#include "grid.h"
#include "levelOne.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockT.h"
#include "blockO.h"
#include "blockS.h"
#include "blockZ.h"

LevelZero::LevelZero(std::string file, int seed):
  Level{0, file, seed}, fileStream{file} {}

Block *LevelZero::newBlock() {
  Block *block = nullptr;
  char input;
  if (not(fileStream >> input)) {
    fileStream.close();
    fileStream.open(getFileName(), std::ifstream::in);
    fileStream >> input;
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
              // maybe add "X" case for testing
    default:
              throw "Unrecognized block type";
  }
  return block;
}

Level *LevelZero::levelUp(Grid *grid) {
  Level *newLevel = new LevelOne{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}

Level *LevelZero::levelDown(Grid *grid) {
  Level *newLevel = new LevelZero{getFileName(), getSeed()};
  newLevel->updateLevel(grid);
  return newLevel;
}
