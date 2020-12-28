#ifndef BLOCK_J_H
#define BLOCK_J_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0| 
 1|
 2|J
 3|JJJ

*/

class BlockJ final: public Block {
  public:
  BlockJ();
  ~BlockJ();
};

#endif
