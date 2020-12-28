#include "level.h"
#include "grid.h"

int Level::getLevelNumber() const {
  return levelNumber;
}

std::string Level::getFileName() const {
  return fileName;
}

int Level::getSeed() const {
  return seed;
}

void Level:: updateLevel(Grid *grid){
  grid->updateLevel(getLevelNumber());
}

void Level:: setNoRandom(std::string file2){
  noRandom = true;
  noRandomFileName = file2;
  noRandomFile.open(noRandomFileName);
}

void Level::setRandom(){
  noRandom = false;
}

Level::~Level() {}
