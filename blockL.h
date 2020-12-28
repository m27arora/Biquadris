#ifndef BLOCK_L_H
#define BLOCK_L_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0| 
 1|
 2|  L
 3|LLL

*/

class BlockL final: public Block {
  public:
  BlockL();
  ~BlockL();
};

#endif
