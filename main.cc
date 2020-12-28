#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "grid.h"
#include "block.h"
#include "levelZero.h"
#include "blockS.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <memory>

using namespace std;

// Helper function for command interpreters, to return what the actual command is

string commandMap(string str){
  // Creating vector of commands
  vector<string> commands = {"left", "right", "down", "clockwise",
    "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random",
    "sequence", "I", "J", "L", "Z", "S", "O", "T", "restart"};

  int count = 0;
  string s; // to store the actual command

  for(int i = 0; i < commands.size(); i++){

    if(commands.at(i).find(str) == 0){
      s = commands.at(i);
      count++;
    }
  }

  if(count == 1){
    return s;
  }
  else{
    return "";
  }

}

void action(Grid *currentGrid, TextDisplay *td) {
  cout << *(td);
  string specialAction;
  cout << endl << "Enter Special Ability:" << endl;
  cin >> specialAction;
  while (specialAction != "blind" && specialAction != "force" && specialAction != "heavy") {
    cout << "Invalid special action (blind, force, heavy):" << endl;
    if (not(cin >> specialAction)) break;
  }
  if (specialAction == "blind") {
    currentGrid->getOtherGrid()->activateBlind();
  } else if (specialAction == "force") {
    char block;
    cin >> block;
    while (block != 'I' && block != 'O' && block != 'T' && block != 'L' 
      && block != 'J' && block != 'S' && block != 'Z') {
      cout << "Invalid Block entered (I, O, T, L, J, S, Z):" << endl;
      if (not(cin >> block)) break;
    }
    currentGrid->getOtherGrid()->forceBlock(block);
  } else if (specialAction == "heavy") {
    currentGrid->getOtherGrid()->activateHeavy();
  }
}

int main(int argc, char *argv[]) {
  bool textOnly = false;

  string scriptfile1 = "sequence1.txt";
  string scriptfile2 = "sequence2.txt";

  int initialSeed = 1;
  int initialLevel = 0;
  bool darkMode = false;

  string option;

  // Reading in command line interface
  for (int i = 1; i < argc; ++i) {
    string option;
    string optionValue;
    istringstream optionStream{argv[i]};
    optionStream >> option;
    try {
      if (option == "-text") {
        textOnly = true;
        cout << "Only text will be displayed" << endl;
      } else if (option == "-seed") {
        istringstream seedStream{argv[i + 1]};
        try {
          seedStream >> initialSeed;
          ++i;
        } catch (...) { cout << "Invalid seed number input" << endl; }
        cout << "Game is played with seed number " << initialSeed << endl;
      } else if (option == "-scriptfile1") {
        istringstream scriptFileStream{argv[i + 1]};
        try {
          scriptFileStream >> scriptfile1;
          ++i;
        } catch (...) { cout << "Invalid sequence file name" << endl; }
        cout << "First scriptfile is " << scriptfile1 << endl;
      } else if (option == "-scriptfile2") {
        istringstream scriptFileStream{argv[i + 1]};
        try {
          scriptFileStream >> scriptfile2;
          ++i;
        } catch (...) { cout << "Invalid sequence file name" << endl; }
        cout << "Second scriptfile is " << scriptfile2 << endl;
      } else if (option == "-startlevel") {
        istringstream levelStream{argv[i + 1]};
        try {
          levelStream >> initialLevel;
          ++i;
        } catch (...) { cout << "Invalid level number input" << endl; }
        cout << "Game is starting from level " << initialLevel << endl;
      } else if (option == "-darkmode") {
        darkMode = true;
      }else {
        throw 1;
      }
    } catch (...) { cout << "Invalid command line interface command" << endl; }
  }

  // Initializing grids
  unique_ptr<TextDisplay> td {new TextDisplay()};
  unique_ptr<GraphicsDisplay> gd {nullptr};
  if (!textOnly) gd.reset(new GraphicsDisplay(darkMode));

  unique_ptr<Grid> gridOne(new Grid(1, scriptfile1, initialSeed, td.get(), gd.get(), initialLevel));
  unique_ptr<Grid> gridTwo(new Grid(2, scriptfile2, initialSeed, td.get(), gd.get(), initialLevel));

  unique_ptr<int> hiscore(new int{0}); // initialising the high score

  gridOne->setOtherGrid(gridTwo.get());
  gridTwo->setOtherGrid(gridOne.get());
  gridOne->setHiScore(hiscore.get());
  gridTwo->setHiScore(hiscore.get());

  Grid *currentGrid = gridOne.get();

  cout << *(td);

  srand(initialSeed); // to generate seed

  vector<string> sequenceCommands; // to store the commands from the sequence file
  string command;
  string cmd;
  string str;
  int multiplier;

  while (true) {
    try {

      if(sequenceCommands.empty()){ // if there are no commands from seqeunce file, then read from stdin
        if(!(cin >> command)){ // if EOF is reached, game ends
          break;
        }
      }
      else{ // read the commands one-by-one from sequence file
        command = sequenceCommands.front();
        sequenceCommands.erase(sequenceCommands.begin()); // remove commands that has already been read
      }

      istringstream ss{command};

      if(!(ss>>multiplier)){ // if no multiplier is provided, then default value of multiplier is 1
        ss.ignore();
        ss.clear();
        multiplier = 1;
      }

      ss>>str; // read the command or its initials
      cmd = commandMap(str); // get the actual command from the helper function

      if (cmd == "left") {
        currentGrid->move(Move::Left, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
      } else if (cmd == "right") {
        currentGrid->move(Move::Right, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
      } else if (cmd == "down") {
        currentGrid->move(Move::Down, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
      } else if (cmd == "clockwise") {
        currentGrid->move(Move::Clock, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
        cout << "CW was called" << endl;
      } else if (cmd == "counterclockwise") {
        currentGrid->move(Move::CounterClock, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
        cout << "CCW was called" <<  endl;
      } else if (cmd == "drop") {
        currentGrid->move(Move::Drop, multiplier);
        if (currentGrid->isTurnOver()) {
          if (currentGrid->isActionRequired()) action(currentGrid, td.get());
          currentGrid = currentGrid->getOtherGrid();
        }
      } else if (cmd == "levelup") {
        currentGrid->levelUp(multiplier);
      } else if (cmd == "leveldown") {
        currentGrid->levelDown(multiplier);
      } else if (cmd == "norandom") {
        cout << "no random was called " << endl;
        string filename;
        cin >> filename;
        currentGrid->noRandom(filename);
        cout << "and sent file: " << filename << endl;
      } else if (cmd == "random") {
        currentGrid->random();
        cout << "random was called" << endl;
      } else if (cmd == "sequence") {
        string filename;
        cin >> filename;
        string s;
        ifstream cmdSequenceFile{filename};

        if(!cmdSequenceFile){
          cerr<<"file does not exist"<<endl;
          continue;
        }
        // reading in the commands from file and storing it in a vector
        while (cmdSequenceFile >> s) {
          sequenceCommands.emplace_back(s);
        }
        continue;
        cout << "sequence was called, executing commands from " << filename << endl;
      } else if (cmd == "I" || cmd == "O" || cmd == "L" || cmd == "J" || cmd == "S" || cmd == "Z" || cmd == "T") {

        if (cmd == "I"){
          currentGrid->forceBlock('I');
        } else if (cmd == "O"){
          currentGrid->forceBlock('O');
        } else if (cmd == "L"){
          currentGrid->forceBlock('L');
        } else if (cmd == "J"){
          currentGrid->forceBlock('J');
        } else if (cmd == "S"){
          currentGrid->forceBlock('S');
        } else if (cmd == "Z"){
          currentGrid->forceBlock('Z');
        } else if (cmd == "T"){
          currentGrid->forceBlock('T');
        }

        cout << cmd << " block will be produced" << endl;
      } else if (cmd == "restart") {

        //reinitialise the textdispaly, graphicsdisplay, both the grids and the highscore

        td.reset(new TextDisplay());
        gd.reset(nullptr);
        if (!textOnly) gd.reset(new GraphicsDisplay(darkMode));

        gridOne.reset(new Grid(1, scriptfile1, initialSeed, td.get(), gd.get(), initialLevel));
        gridTwo.reset(new Grid(2, scriptfile2, initialSeed, td.get(), gd.get(), initialLevel));

        gridOne->setOtherGrid(gridTwo.get());
        gridTwo->setOtherGrid(gridOne.get());
        gridOne->setHiScore(hiscore.get());
        gridTwo->setHiScore(hiscore.get());

        currentGrid = gridOne.get();

        cout << *(td);


        cout << "restarted" << endl;
      } else {
        throw 1;
      }
      cout << *(td);
    } catch (char const *exception) {
      cout << *(td);
      cout << exception << endl;
    } catch (string exception) {
      cout << *(td);
      cout << exception << " " << endl;
    } catch (...) { cout << "Invalid Input" << endl; }
  }
}
