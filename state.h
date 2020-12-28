#ifndef STATE_H
#define STATE_H

#include "block.h"
#include "position.h"

/* Change types are:
    Score  -- Grid has updated the score and/or highscore. I'm letting you know
              in case you need to change display (for text and graphics display).

    Level  -- I have changed the level I am now. You might need to change stuff

    EBlock -- I am a cell whose type has just changed

    NextBlock -- Grid has updated the nextBlock for one of the grids. Just letting
                 thou know.

    Blind -- A cell has been blinded

    GameOver -- The game is over, notifying text and graphics display,
                gridNum is 1 or 2 for the winner, 0 if it is a tie
*/


enum class ChangeType {Score,Level,Eblock,NextBlock,Blind,GameOver};

struct State {
	int score;
	int hiScore;
	int level;
	EBlock block;
	Position cellPosition;
	int gridNum;
	ChangeType change;
	EBlock nextBlock;
};

#endif
