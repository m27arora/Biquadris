#include "textdisplay.h"
#include "subject.h"

using namespace std;

TextDisplay::TextDisplay(){		

  vector<char> vec;

  for(int j=0;j<11;j++){
    vec.emplace_back(' ');
  }
  for(int i=0;i<18;i++){
    gridOneDisplay.emplace_back(vec);
    gridTwoDisplay.emplace_back(vec);
  }
}

void TextDisplay::notify(Subject &whoNotified){
  State state = whoNotified.getState();
  HiScore=state.hiScore;
  turn=state.gridNum;

  if(state.change == ChangeType::Level){
    if(state.gridNum == 1)
      levelOne = state.level;
    else if(state.gridNum == 2)
      levelTwo = state.level;
  }

  else if(state.change == ChangeType:: Score){
    if(state.gridNum == 1)
      scoreOne = state.score;
    else if(state.gridNum == 2)
      scoreTwo = state.score;
  }

  else if(state.change == ChangeType::NextBlock){
    if(state.gridNum == 1){
      nextBlockOne = state.nextBlock;
      //nextBlockTwo = EBlock::Empty;
    }
    else if(state.gridNum==2){
      nextBlockTwo = state.nextBlock;
      //nextBlockOne = EBlock::Empty;
    }
  }
  
  else if(state.gridNum==1 && (state.change == ChangeType::Blind)){
    gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='?';
  }

  else if(state.gridNum==2 && (state.change == ChangeType::Blind)){
    gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='?';
  }

  else if(state.gridNum==1 && (state.change == ChangeType::Eblock)){

    if(state.block == EBlock::I)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='I';
    else if(state.block == EBlock::J)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='J';
    else if(state.block == EBlock::L)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='L';
    else if(state.block == EBlock::T)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='T';
    else if(state.block == EBlock::O)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='O';
    else if(state.block == EBlock::S)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='S';
    else if(state.block == EBlock::Z)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='Z';
    else if(state.block == EBlock::X)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]='*';
    else if(state.block == EBlock::Empty)
      gridOneDisplay[state.cellPosition.y][state.cellPosition.x]=' ';
  }

  else if(state.gridNum==2 && (state.change == ChangeType::Eblock)){

    if(state.block == EBlock::I)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='I';
    else if(state.block == EBlock::J)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='J';
    else if(state.block == EBlock::L)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='L';
    else if(state.block == EBlock::T)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='T';
    else if(state.block == EBlock::O)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='O';
    else if(state.block == EBlock::S)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='S';
    else if(state.block == EBlock::Z)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='Z';
    else if(state.block == EBlock::X)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]='*';
    else if(state.block == EBlock::Empty)
      gridTwoDisplay[state.cellPosition.y][state.cellPosition.x]=' ';
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {

  out << "High Score: "<< td.HiScore <<endl;
  out << "Level: " << td.levelOne << "\t" <<"Level: "<< td.levelTwo << endl;
  out << "Score: " << td.scoreOne << "\t" <<"Score: " << td.scoreTwo << endl;
  out << "-----------" << "\t" << "-----------" << endl;

  for(int j = 0; j < 18; ++j) {
    for(int i = 0 ;i < 11; ++i) {
      out << td.gridOneDisplay[j][i];
      if (i == 10) {
        cout << "\t";
        for (int k = 0; k < 11; k++) {
          out << td.gridTwoDisplay[j][k];
          if(k == 10) {
            out << endl;
          }
        }
      }
    }
  }

  out << "-----------" << "\t" << "-----------" << endl;
  out << "Next:\t\tNext:" << endl;
  string firstLine = "";
  string secondLine = "";
  if (td.nextBlockOne == EBlock::I){
    secondLine += "IIII";
  } else if(td.nextBlockOne == EBlock::J){
    firstLine += "J";
    secondLine += "JJJ";
  } else if(td.nextBlockOne == EBlock::L){
    firstLine += "  L";
    secondLine += "LLL";
  } else if(td.nextBlockOne == EBlock::O){
    firstLine += "OO";
    secondLine += "OO";
  } else if(td.nextBlockOne == EBlock::S){
    firstLine += " SS";
    secondLine += "SS ";
  } else if(td.nextBlockOne == EBlock::Z){
    firstLine += "ZZ ";
    secondLine += " ZZ";
  } else if(td.nextBlockOne == EBlock::T){
    firstLine += "TTT";
    secondLine += " T ";
  }

  firstLine += "\t\t";
  secondLine += "\t\t";

  if (td.nextBlockTwo == EBlock::I) {
    out << firstLine << endl;
    out << secondLine << "IIII" << endl;
  }
  else if(td.nextBlockTwo == EBlock::J){
    out << firstLine << "J" << endl;
    out << secondLine << "JJJ" << endl;
  }
  else if(td.nextBlockTwo == EBlock::L){
    out<< firstLine << "  L" << endl;
    out<< secondLine << "LLL" << endl;
  }
  else if(td.nextBlockTwo == EBlock::O){
    out << firstLine << "OO" << endl;
    out << secondLine << "OO" << endl;
  }
  else if(td.nextBlockTwo == EBlock::S){
    out << firstLine << " SS" << endl;
    out << secondLine << "SS " << endl;
  }
  else if(td.nextBlockTwo == EBlock::Z){
    out << firstLine << "ZZ " << endl;
    out << secondLine << " ZZ" << endl;
  }
  else if(td.nextBlockTwo == EBlock::T){
    out << firstLine << "TTT" << endl;
    out << secondLine << " T " << endl;
  }

  return out;
}
