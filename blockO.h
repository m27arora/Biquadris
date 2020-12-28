#ifndef BLOCK_O_H
#define BLOCK_O_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0| 
 1|
 2|OO
 3|OO

*/

class BlockO final: public Block {
  public:
  BlockO();
  ~BlockO();
};

#endif
