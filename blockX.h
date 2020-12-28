#ifndef BLOCK_X_H
#define BLOCK_X_H
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

class BlockX final: public Block {
  public:
  BlockX();
  ~BlockX();
};

#endif
