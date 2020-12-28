#ifndef BLOCK_Z_H
#define BLOCK_Z_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0|
 1|  
 2|ZZ
 3| ZZ

*/

class BlockZ final: public Block {
  public:
  BlockZ();
  ~BlockZ();
};

#endif
