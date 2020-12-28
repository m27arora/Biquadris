#ifndef BLOCK_T_H
#define BLOCK_T_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0| 
 1|
 2|TTT
 3| T

*/

class BlockT final: public Block {
  public:
  BlockT();
  ~BlockT();
};

#endif
