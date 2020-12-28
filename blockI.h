#ifndef BLOCK_I_H
#define BLOCK_I_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   0123
   ----
 0|
 1| 
 2|
 3|IIII

*/

class BlockI final: public Block {
  public:
  BlockI();
  ~BlockI();
};

#endif
