#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cstdlib>
#include "observer.h"
#include "subject.h"
#include "cell.h"
#include "level.h"
#include "block.h"
#include "state.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <map>

const int HEIGHT = 18;
const int WIDTH = 11;

enum class Move {Right, Left, Down, Drop, CounterClock, Clock};

class Grid final: public Observer, public Subject {
	std::vector<std::vector<Cell>> theGrid;
  std::unique_ptr<Level> level;
	int gridNum;
	Grid *otherGrid = nullptr;
  std::shared_ptr<Block> currentBlock;
  std::shared_ptr<Block> nextBlock;
  TextDisplay *td = nullptr;
  int levelNum = 0;
  int score = 0;
  int *hiscore = nullptr;
  bool turnOver = false;
  bool actionRequired = false;
  bool isCellAvailable(Position &newP, const std::vector<Position> &original) const;
  // checks if cell is available to move to
  bool translateBlock(std::vector<Position> &newPositions, Position &bl);
  void newTurn();
  void checkRows(); // Wrapper functions to check for any rows that are filled
  bool heavyActivated = false;
  bool blindActivated = false;
  bool isRowFull(const int &rowNumber) const; //Checks if rowNumber is filled
  void clearRow(const int &rowNumber); //removes row and moves whole grid one level down
  bool posnExists(const std::vector<Position> &original, Position &newP) const;
  // checks if newP exists in original
  int currBlockLevel;
  int nextBlockLevel;
  void right(int mult = 1);
  void left(int mult = 1);
  bool down(int mult = 1); // sets block and ends turn if block cannot move down
  // down is true if move is successful
  void clockwise(int mult = 1); // Rotates currentBlock Clockwise
  void counterClockwise(int mult = 1); // Rotates currentBlock Counterclockwise
  void drop(int mult = 1);
  struct BlockCounter {
    int level; // the level that the block was generated at
    int numRemaining; // number of squares of a block still on the grid
  };
  int blockID = 0; // each block that is set needs an ID
  int getNewID(); // creates a new ID
  std::map<int, BlockCounter> PlacedBlocks;
  int playsWithoutClear = 0;
  void dropXBlock(); // drops * Block in Level 4
  int getHighX() const; // Gets the Highest X value for the currentBlock
  int getLowX() const;  // Gets the Lowest X value for the currentBlock
  int getHighY() const; // Gets the Highest Y value for the currentBlock
  int getLowY() const;  // Gets the Lowest Y value for the currentBlock
	public:
	Grid(int gridNum, std::string &file, int seed = 0, TextDisplay *td = nullptr,
    GraphicsDisplay *gd = nullptr, int levelNum = 0);
  Grid* getOtherGrid() const;
  void setHiScore(int *hs);
  void levelUp(int mult = 1);
  void levelDown(int mult = 1);
  void unPlaceCurrentBlock();
  // removes the current block from the position it is at 
  int getScore() const ;
  int getGridNumber() const ;
  bool placeCurrentBlock();
  // places the current block at its initial position, true if successful
  void setOtherGrid(Grid *other);
  void move(Move direction, int mult = 1);
  void updateLevel(int levelNum);
  bool isBlindActive() const ;
  void activateBlind();
  // Updates the appopriate cells to show blind box
  void deactivateBlind();
  // Updates the appropriate cells to show original cell block 
  bool isHeavyActive() const ;
  void activateHeavy();
  // Sets own heavy bool to true
  void deactivateHeavy();
  // Sets own heavy bool to false
  void forceBlock(const char &block);
  // Unplaces current block, creates a new &block and places it
  void notify(Subject &whoFrom) override;
  bool isTurnOver();
  bool isActionRequired();
  void noRandom(std::string filename);
  void random();
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

std::ostream &operator<<(std::ostream &out, const Grid &g);

#endif
