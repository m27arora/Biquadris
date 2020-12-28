#include "graphicsdisplay.h"
#include "subject.h"
#include "state.h"
#include <sstream>
#include <vector>

GraphicsDisplay::GraphicsDisplay(bool darkMode) {
  theDisplay = std::make_unique<Xwindow>(windowWidth, windowHeight);
  if (darkMode) {
    textColour = Xwindow::White;
    backgroundColour = Xwindow::Black;
    theDisplay->fillRectangle(0, 0, windowWidth, windowHeight, backgroundColour);
  }

  // set up hiscore, score and level
  theDisplay->drawString(550, 10, "Hiscore: 0", textColour);
  theDisplay->drawString(380, 20, "Level: 0", textColour);
  theDisplay->drawString(100, 20, "Score: 0", textColour);
  theDisplay->drawString(980, 20, "Level: 0", textColour);
  theDisplay->drawString(700, 20, "Score: 0", textColour);

  // set up two grids
  Position gridOrigin {grid1Origin};
  for (int i = 0; i < 2; ++i) {
    theDisplay->fillRectangle(gridOrigin.x - gridAxisWidth, gridOrigin.y,
      gridAxisWidth, cellSize * HEIGHT, textColour);
    theDisplay->fillRectangle(gridOrigin.x - gridAxisWidth,
      gridOrigin.y + cellSize * HEIGHT, cellSize * WIDTH + gridAxisWidth,
      gridAxisWidth, textColour);
    theDisplay->fillRectangle(gridOrigin.x + cellSize * WIDTH,
      gridOrigin.y - gridAxisWidth, gridAxisWidth,
      cellSize * HEIGHT + 2 * gridAxisWidth, textColour);
    theDisplay->fillRectangle(gridOrigin.x - gridAxisWidth,
      gridOrigin.y - gridAxisWidth, cellSize * WIDTH + gridAxisWidth,
      gridAxisWidth, textColour);

    int x = gridOrigin.x;
    int y = gridOrigin.y;

    for (int j = 1; j < WIDTH; ++j) {
      theDisplay->drawLine(x + cellSize * j, y,
        x + cellSize * j, y + cellSize * HEIGHT);
    }
    for (int j = 1; j < HEIGHT; ++j) {
      theDisplay->drawLine(x, y + cellSize * j,
        x + cellSize * WIDTH, y + cellSize * j);
    }

    y += cellSize * HEIGHT + 20;
    theDisplay->drawString(x, y, "Next:", textColour);

    gridOrigin = grid2Origin;
  }
}

int GraphicsDisplay::getColour(EBlock &b) const {
  int colour;
  switch (b) {
    case EBlock::J: colour = Xwindow::Blue;
                    break;
    case EBlock::L: colour = Xwindow::Orange;
                    break;
    case EBlock::O: colour = Xwindow::Yellow;
                    break;
    case EBlock::S: colour = Xwindow::Green;
                    break;
    case EBlock::T: colour = Xwindow::Magenta;
                    break;
    case EBlock::Z: colour = Xwindow::Red;
                    break;
    case EBlock::I: colour = Xwindow::Cyan;
                    break;
    case EBlock::X: colour = Xwindow::Brown;
                    break;
    default: colour = backgroundColour;
    }
    return colour;
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  State s = whoNotified.getState();
  if (s.change == ChangeType::Eblock) {
    int x = 1; // x and y start at 1 to not draw over grid overlay
    int y = 1;
    if (s.gridNum == 1) {
      x += grid1Origin.x;
      y += grid1Origin.y;
    } else {
      x += grid2Origin.x;
      y += grid2Origin.y;
    }
    x += s.cellPosition.x * cellSize;
    y += s.cellPosition.y * cellSize;
    int colour = getColour(s.block);
    theDisplay->fillRectangle(x, y, cellSize - 1, cellSize - 1, colour);
    // cellSize is subtracted by 1 to not draw over grid overlay
  } else if (s.change == ChangeType::Score) {
    std::ostringstream hiScore;
    hiScore << "Hiscore: " << s.hiScore;
    theDisplay->fillRectangle(550, 0, 100, 10, backgroundColour);
    theDisplay->drawString(550, 10, hiScore.str(), textColour);

    int x = s.gridNum == 1 ? 100 : 700;
    int y = 20;
    std::ostringstream score;
    score << "Score: " << s.score;
    theDisplay->fillRectangle(x, y - 10, 60, 10, backgroundColour);
    theDisplay->drawString(x, y, score.str(), textColour);
  } else if (s.change == ChangeType::Level) {
    int x = s.gridNum == 1 ? 380 : 980;
    int y = 20;
    std::ostringstream level;
    level << "Level: " << s.level;
    theDisplay->fillRectangle(x, 10, 60, 10, backgroundColour);
    theDisplay->drawString(x, y, level.str(), textColour);
   } else if (s.change == ChangeType::NextBlock) {
    int x = s.gridNum == 1 ? 101 : 701;
    int y = grid1Origin.y + cellSize * HEIGHT + 30 + 11;
    theDisplay->fillRectangle(x, y, cellSize * 4, cellSize * 2, backgroundColour);
    int colour = getColour(s.nextBlock);
    std::vector<Position> positions;

    if (s.nextBlock == EBlock::I) {
      positions.emplace_back(Position{0, 1});
      positions.emplace_back(Position{1, 1});
      positions.emplace_back(Position{2, 1});
      positions.emplace_back(Position{3, 1});
    } else if (s.nextBlock == EBlock::J) {
      positions.emplace_back(Position{0, 0});
      positions.emplace_back(Position{0, 1});
      positions.emplace_back(Position{1, 1});
      positions.emplace_back(Position{2, 1});
    } else if (s.nextBlock == EBlock::L) {
      positions.emplace_back(Position{0, 1});
      positions.emplace_back(Position{1, 1});
      positions.emplace_back(Position{2, 1});
      positions.emplace_back(Position{2, 0});
    } else if (s.nextBlock == EBlock::O) {
      positions.emplace_back(Position{0, 0});
      positions.emplace_back(Position{0, 1});
      positions.emplace_back(Position{1, 0});
      positions.emplace_back(Position{1, 1});
    } else if (s.nextBlock == EBlock::S) {
      positions.emplace_back(Position{0, 1});
      positions.emplace_back(Position{1, 1});
      positions.emplace_back(Position{1, 0});
      positions.emplace_back(Position{2, 0});
    } else if (s.nextBlock == EBlock::Z) {
      positions.emplace_back(Position{0, 0});
      positions.emplace_back(Position{1, 0});
      positions.emplace_back(Position{1, 1});
      positions.emplace_back(Position{2, 1});
    } else if (s.nextBlock == EBlock::T) {
      positions.emplace_back(Position{0, 0});
      positions.emplace_back(Position{1, 0});
      positions.emplace_back(Position{2, 0});
      positions.emplace_back(Position{1, 1});
    }

    for (auto &p : positions) {
      p.x = x + p.x * cellSize;
      p.y = y + p.y * cellSize;
      theDisplay->fillRectangle(p.x, p.y,
        cellSize - 1, cellSize - 1, colour);
      // cellSize is subtracted by 1 to not draw over grid overlay
    }
  } else if (s.change == ChangeType::Blind) {
    int x = 1; // x and y start at 1 to not draw over grid overlay
    int y = 1;
    if (s.gridNum == 1) {
      x += grid1Origin.x;
      y += grid1Origin.y;
    } else {
      x += grid2Origin.x;
      y += grid2Origin.y;
    }
    x += s.cellPosition.x * cellSize;
    y += s.cellPosition.y * cellSize;
    
    theDisplay->fillRectangle(x, y, cellSize - 1, cellSize - 1, backgroundColour);
    // cellSize is subtracted by 1 to not draw over grid overlay
    theDisplay->drawString(x + cellSize / 2, y + cellSize / 2, "?", textColour);
  } else if (s.change == ChangeType::GameOver) {
    theDisplay->fillRectangle(300, 200, 500, 300, backgroundColour);
    if (s.gridNum == 1) {
      theDisplay->drawString(500, 350, "PLAYER 1 WINS", textColour);
    } else if (s.gridNum == 2) {
      theDisplay->drawString(500, 350, "PLAYER 2 WINS", textColour);
    } else {
      theDisplay->drawString(550, 350, "TIE!", textColour);
    }
  }
}
