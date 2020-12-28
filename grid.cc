#include "grid.h"
#include "levelZero.h"
#include "levelOne.h"
#include "blockZ.h"
#include "blockI.h"
#include "blockS.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockT.h"
#include "blockX.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
using namespace std;

Grid::Grid(int gridNum, string &file, int seed,
    TextDisplay *td, GraphicsDisplay *gd, int levelNum):
  gridNum{gridNum}, td{td}, levelNum{levelNum} {
    for (int i = 0; i < HEIGHT; ++i) {
      vector<Cell> cellRow;
      for (int j = 0; j < WIDTH; ++j) {
        Cell newCell(j, i);
        newCell.attach(this);
        cellRow.emplace_back(newCell);
      }
      theGrid.emplace_back(cellRow);
    }
    switch(levelNum) {
      case 1 : level = make_unique<LevelOne>(file, seed);
               break;
      case 2 : level = make_unique<LevelTwo>(file, seed);
               break;
      case 3 : level = make_unique<LevelThree>(file, seed);
               break;
      case 4 : level = make_unique<LevelFour>(file, seed);
               break;
      default: level = make_unique<LevelZero>(file, seed);
               break;
    }
    if (td != nullptr) attach(td);
    if (gd != nullptr) attach(gd);
    currentBlock.reset(level->newBlock());
    nextBlock.reset(level->newBlock());
    currBlockLevel = levelNum;
    nextBlockLevel = levelNum;
    placeCurrentBlock();
    // states given {-1, -1} for the position so observers do not try
    //   to unecessarily change a cell
    setState(State {0, 0, levelNum, EBlock::Empty, Position{-1, -1},
        gridNum, ChangeType::Level, nextBlock->getType()});
    notifyObservers();
    setState(State {0, 0, levelNum, EBlock::Empty, Position{-1, -1},
        gridNum, ChangeType::NextBlock, nextBlock->getType()});
    notifyObservers(); 
  }

void Grid::setHiScore(int *hs) {
  hiscore = hs;
  State newState = getState();
  newState.change = ChangeType::Score;
  newState.score = score;
  newState.hiScore = *hiscore;
  setState(newState);
  notifyObservers();
}

void Grid::setOtherGrid(Grid *other) {
  otherGrid = other;
}

Grid *Grid::getOtherGrid() const {
  return otherGrid;
}

bool Grid::posnExists(const std::vector<Position> &original, Position &newP) const {
  bool exists = false;
  for(auto &p : original) {
    if (p.x == newP.x && p.y == newP.y) {
      exists = true;
      break;
    }
  }
  return exists;
}

bool Grid::isCellAvailable(Position &newP, const std::vector<Position> &original) const {
  return newP.x < WIDTH && newP.x >= 0 &&
    newP.y < HEIGHT && newP.y >= 0 &&
    (theGrid[newP.y][newP.x].getBlock() == EBlock::Empty ||
     posnExists(original, newP));
}

bool Grid::translateBlock(std::vector<Position> &newPositions, Position &bl) {
  if (currentBlock->getIsSet()) return false;
  const vector<Position> original = currentBlock->getPositions();
  bool validMove = true;
  for (auto &p : newPositions) {
    validMove = validMove && isCellAvailable(p, original);
  }
  if (validMove) {
    currentBlock->setPositions(newPositions);
    currentBlock->setBottomLeft(bl);
    for (auto &p : original) {
      theGrid[p.y][p.x].setBlock(EBlock::Empty);
    }
    for (auto &p : currentBlock->getPositions()) {
      theGrid[p.y][p.x].setBlock(currentBlock->getType());
    }
    return true;
  } else {
    return false;
  }
}

void Grid::dropXBlock() {
  if (level->getLevelNumber() != 4) return;
  unPlaceCurrentBlock();
  playsWithoutClear = 0;
  shared_ptr<Block> temp = nextBlock;
  nextBlock = currentBlock;
  currentBlock = make_shared<BlockX>();
  if (not(placeCurrentBlock())) {
    int winnerGridNum = 0;
    if (getScore() > getOtherGrid()->getScore()) winnerGridNum = getGridNumber();
    if (getScore() < getOtherGrid()->getScore()) winnerGridNum = getOtherGrid()->getGridNumber();
    
    State newState = getState();
    newState.change = ChangeType::GameOver;
    newState.gridNum = winnerGridNum;
    setState(newState);
    notifyObservers();

    winnerGridNum == 0 ? throw ("IT IS A TIE!"): throw ("Player " + to_string(winnerGridNum) + " has WON!");
  }
  move(Move::Drop, 1);
  nextBlock = temp;
  placeCurrentBlock();
  playsWithoutClear = 0;
}

void Grid::unPlaceCurrentBlock() {
  vector<Position> positions = currentBlock->getPositions();
  for (auto &p : positions) {
    theGrid[p.y][p.x].setBlock(EBlock::Empty);
  }
}

bool Grid::placeCurrentBlock() {
  vector<Position> positions = currentBlock->getPositions();
  for (auto &p : positions) {
    if (theGrid[p.y][p.x].getBlock() != EBlock::Empty) return false;
  }
  for (auto &p : positions) {
    EBlock eb = currentBlock->getType();
    theGrid[p.y][p.x].setBlock(eb);
  }

  State newState = getState();
  newState.change = ChangeType::NextBlock;
  newState.nextBlock = nextBlock->getType();
  setState(newState);
  notifyObservers();

  return true;
}

void Grid::newTurn() {
  currentBlock = nextBlock;
  currBlockLevel = nextBlockLevel;
  nextBlock.reset(level->newBlock());
  nextBlockLevel = level->getLevelNumber();

  if (isBlindActive()) deactivateBlind();

  if (isHeavyActive()) deactivateHeavy();

  // This is to check if the current block could not be placed
  // (i.e theres a another block in the way)
  if (not(placeCurrentBlock())) {
    int winnerGridNum = 0;
    if (getScore() > getOtherGrid()->getScore()) winnerGridNum = getGridNumber();
    if (getScore() < getOtherGrid()->getScore()) winnerGridNum = getOtherGrid()->getGridNumber();
   
    // Set state to notify Observers of Game over
    State newState = getState();
    newState.change = ChangeType::GameOver;
    newState.gridNum = winnerGridNum;
    setState(newState);
    notifyObservers();
    
    // Exception thrown after game is over
    winnerGridNum == 0 ? throw ("IT IS A TIE!"): throw ("Player " + to_string(winnerGridNum) + " has WON!");
  }

  turnOver = true;
}

int Grid::getGridNumber() const { return gridNum; }

void Grid::checkRows() {
  int count = 0;
  for (int row = 0; row < HEIGHT; ++row) {
    if (isRowFull(row)) {
      clearRow(row);
      ++count;
      playsWithoutClear = 0;
    }
  }
  if (count > 0) {
    score += ((level->getLevelNumber() + count) * (level->getLevelNumber() + count));
    vector<int> clearedBlockIDs;
    for (auto &p : PlacedBlocks) {
      if (p.second.numRemaining <= 0) {
        score += ((p.second.level + 1) * (p.second.level + 1));
        clearedBlockIDs.emplace_back(p.first);
      }
    }
    for (auto &id : clearedBlockIDs) {
      PlacedBlocks.erase(id);
    }
    if (score >= *hiscore) { *hiscore = score; }

    // Set state to notify Observers of score/highscore change
    State newState = getState();
    newState.change = ChangeType::Score;
    newState.score = score;
    newState.hiScore = *hiscore;
    setState(newState);
    notifyObservers();

    if (count >= 2) {
      actionRequired = true;
    }
  }
}

bool Grid::isRowFull(const int &rowNumber) const {
  for (int column = 0; column < WIDTH; ++column) {
    if (theGrid.at(rowNumber).at(column).getBlock() == EBlock::Empty) return false;
  }
  return true;
}

void Grid::clearRow(const int &rowNumber) {
  for (int row = rowNumber; row >= 1; --row) {
    for (int column = 0; column < WIDTH; ++column) {
      Cell &currCell = theGrid.at(row).at(column);
      Cell &cellAbove = theGrid.at(row - 1).at(column);
      if (row == rowNumber && PlacedBlocks.count(currCell.getBlockID())) {
        PlacedBlocks.at(currCell.getBlockID()).numRemaining -= 1;
      }
      currCell.setBlockID(cellAbove.getBlockID());

      // If the block is the same as the one right above..nothing happens
      // Helps optimize Xwindow
      if (currCell.getBlock() == cellAbove.getBlock()) continue;
      currCell.setBlock(cellAbove.getBlock());
    }
  }

  // -1 is non-existant in the placed blocks, helps represent an empty block
  for (int column = 0; column < WIDTH; ++column) {
    theGrid.at(0).at(column).setBlock(EBlock::Empty);
    theGrid.at(0).at(column).setBlockID(-1);
  }
}

int Grid::getScore() const { return score; }

void Grid::move(Move direction, int mult) {
  if (direction == Move::Left) {
    left(mult);
  } else if (direction == Move::Right) {
    right(mult);
  } else if (direction == Move::Down) {
    bool success = down(mult);
    if (!success) return;
  } else if (direction == Move::Drop) {
    drop(mult);
    return;
  } else if (direction == Move::CounterClock) {
    counterClockwise(mult);
  } else if (direction == Move::Clock) {
    clockwise(mult);
  } else {
  }

  if (isHeavyActive() && (direction == Move::Right || direction == Move::Left)) { 
    if (down()) {
      if (not(down())) return; 
    } else return;
  }

  if (level->getLevelNumber() >= 3) down();
}

void Grid::right(int mult) {
  if (currentBlock->getIsSet()) return;
  for (int i = 0; i < mult; ++i) {
    const vector<Position> original = currentBlock->getPositions();
    vector<Position> newPositions;
    for (auto &p : original) {
      newPositions.emplace_back(Position{p.x + 1, p.y});
    }
    Position bl = currentBlock->getBottomLeft();
    bl.x += 1;
    translateBlock(newPositions, bl);
  }
}

void Grid::left(int mult) {
  if (currentBlock->getIsSet()) return;
  for (int i = 0; i < mult; ++i) {
    const vector<Position> original = currentBlock->getPositions();
    vector<Position> newPositions;
    for (auto &p : original) {
      newPositions.emplace_back(Position{p.x - 1, p.y});
    }
    Position bl = currentBlock->getBottomLeft();
    bl.x -= 1;
    translateBlock(newPositions, bl);
  }
}

bool Grid::down(int mult) {
  if (currentBlock->getIsSet()) return false;
  bool successful = true;
  for (int i = 0; i < mult; ++i) {
    const vector<Position> original = currentBlock->getPositions();
    vector<Position> newPositions;
    for (auto &p : original) {
      newPositions.emplace_back(Position{p.x, p.y + 1});
    }
    Position bl = currentBlock->getBottomLeft();
    bl.y += 1;
    successful = translateBlock(newPositions, bl);
    if (!successful) {
      // if block cannot move down, block must be set in place
      currentBlock->set();
      int newID = getNewID();
      PlacedBlocks[newID] = BlockCounter{currBlockLevel, 0};
      for (auto &p : currentBlock->getPositions()) {
        theGrid[p.y][p.x].setBlockID(newID);
        PlacedBlocks.at(newID).numRemaining += 1;
      }
      ++playsWithoutClear;
      checkRows(); // sets playsWithoutClear to 0 if necessary
      newTurn();
      if (playsWithoutClear >= 5) dropXBlock();
      return false;
    }
  }
  return true;
}

int Grid::getHighX() const {
  const vector<Position> original = currentBlock->getPositions();
  int high = 0;
  for (auto &p : original) {
    if (p.x > high) high = p.x;
  }
  return high;
}

int Grid::getLowX() const {
  const vector<Position> original = currentBlock->getPositions();
  int low = WIDTH;
  for (auto &p : original) {
    if (p.x < low) low = p.x;
  }
  return low;
}

int Grid::getHighY() const {
  const vector<Position> original = currentBlock->getPositions();
  int high = 0;
  for (auto &p : original) {
    if (p.y > high) high = p.y;
  }
  return high;
}

int Grid::getLowY() const {
  const vector<Position> original = currentBlock->getPositions();
  int low = HEIGHT;
  for (auto &p : original) {
    if (p.y < low) low = p.y;
  }
  return low;
}

void Grid::clockwise(int mult) {
  if (currentBlock->getIsSet()) return;
  for (int i = 0; i < mult; ++i) {
    const vector<Position> original = currentBlock->getPositions();
    vector<Position> newPositions;
    Position bl = currentBlock->getBottomLeft();
    for (auto &p : original) {
      newPositions.emplace_back(Position{ bl.x + (abs(bl.y - p.y)), 
          bl.y + (abs(bl.x - p.x)) - (getHighX() - getLowX()) });
    }
    Position originalBl = currentBlock->getBottomLeft();
    translateBlock(newPositions, originalBl);
  }
}

void Grid::counterClockwise(int mult) {
  if (currentBlock->getIsSet()) return;
  for (int i = 0; i < mult; ++i) {
    const vector<Position> original = currentBlock->getPositions();
    vector<Position> newPositions;
    Position bl = currentBlock->getBottomLeft();
    for (auto &p : original) {
      newPositions.emplace_back(Position{ bl.x - (abs(bl.y - p.y)) + (getHighY() - getLowY()),
          bl.y - (abs(bl.x - p.x))});
    }
    Position originalBl = currentBlock->getBottomLeft();
    translateBlock(newPositions, originalBl);
  }
}

void Grid::drop(int mult) {
  for (int i = 0; i < mult; ++i) {
    while(down());
    if (i < mult - 1) placeCurrentBlock();
  }
}

void Grid::updateLevel(int levelNum) {
  setState(State {score, *hiscore, levelNum, EBlock::Empty, Position{-1, -1},
      gridNum, ChangeType::Level, nextBlock->getType()});
  notifyObservers();
  playsWithoutClear = 0;
}

void Grid::levelUp(int mult) {
  for (int i = 0; i < mult; ++i) {
    level.reset(level->levelUp(this));
  }
}

void Grid::levelDown(int mult) {
  for (int i = 0; i < mult; ++i) {
    level.reset(level->levelDown(this));
  }
}

bool Grid::isBlindActive() const {
  return blindActivated;
}

void Grid::activateBlind(){
  if (not(isBlindActive())) {
    for (int row = 2; row < 12; ++row) {
      for (int column = 2; column < 9; column++) {
        theGrid.at(row).at(column).setVisibility(false);
      }
    }
    blindActivated = true;
    placeCurrentBlock();
  } else return;
}

void Grid::deactivateBlind(){
  if (isBlindActive()) {
    for (int row = 2; row < 12; ++row) {
      for (int column = 2; column < 9; column++) {
        theGrid.at(row).at(column).setVisibility(true);
      }
    }
    blindActivated = false;
  } else return;
}

bool Grid::isHeavyActive() const {
  return heavyActivated;
}

void Grid::activateHeavy() {
  heavyActivated = true;
  placeCurrentBlock();
}
void Grid::deactivateHeavy() {
  heavyActivated = false;
}


void Grid::forceBlock(const char &block) {
  unPlaceCurrentBlock();

  switch(block) {
    case ('I'): currentBlock = make_shared<BlockI>();
                break;
    case ('J'): currentBlock = make_shared<BlockJ>();
                break;
    case ('L'): currentBlock = make_shared<BlockL>();
                break;
    case ('T'): currentBlock = make_shared<BlockT>();
                break;
    case ('O'): currentBlock = make_shared<BlockO>();
                break;
    case ('S'): currentBlock = make_shared<BlockS>();
                break;
    case ('Z'): currentBlock = make_shared<BlockZ>();
                break;
    default:
                throw "Unrecognized block type";
  }

  // This is to check if the current block could not be placed
  // (i.e theres a another block in the way)
  if (not(placeCurrentBlock())) {
    int winnerGridNum = 0;
    if (getScore() > getOtherGrid()->getScore()) winnerGridNum = getGridNumber();
    if (getScore() < getOtherGrid()->getScore()) winnerGridNum = getOtherGrid()->getGridNumber();

    // Set state to notify observers of game over
    State newState = getState();
    newState.change = ChangeType::GameOver;
    newState.gridNum = winnerGridNum;
    setState(newState);
    notifyObservers();
    
    // Throw an exception saying game is over
    winnerGridNum == 0 ? throw ("IT IS A TIE!"): throw ("Player " + to_string(winnerGridNum) + " has WON!");
  }
}

void Grid::notify(Subject &whoFrom) {
  State newS = whoFrom.getState();
  newS.score = score;
  if (hiscore) { newS.hiScore = *hiscore; } 
  else { newS.hiScore = 0; }
  newS.level = levelNum;
  newS.gridNum = gridNum;
  newS.nextBlock = nextBlock->getType();
  setState(newS);
  notifyObservers();
}

bool Grid::isTurnOver() {
  bool returnVal = turnOver;
  turnOver = false;
  return returnVal;
}

bool Grid::isActionRequired() {
  bool returnVal = actionRequired;
  actionRequired = false;
  return returnVal;
}

void Grid:: noRandom(std::string fileName){
  level->setNoRandom(fileName);
}

void Grid:: random(){
  level->setRandom();
}

int Grid::getNewID() { return blockID++; }

ostream &operator<<(ostream &out, const Grid &g) { return out << *(g.td); }
