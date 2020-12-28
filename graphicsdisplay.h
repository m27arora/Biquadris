#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include "position.h"
#include <memory>
#include "window.h"

enum class EBlock;

class GraphicsDisplay: public Observer {
  std::unique_ptr<Xwindow> theDisplay;
  const int windowHeight = 700;
  const int windowWidth = 1200;
  const int cellSize = 30;
  const int gridAxisWidth = 5;
  const int HEIGHT = 18;
  const int WIDTH = 11;
  Position grid1Origin {100, 30};
  Position grid2Origin {700, 30};
  int textColour = Xwindow::Black;
  int backgroundColour = Xwindow::White;
  int getColour(EBlock &b) const;
 public:
  GraphicsDisplay(bool darkMode = false);
  void notify(Subject &whoNotified) override;
};
#endif
