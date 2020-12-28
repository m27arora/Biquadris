#ifndef BLOCK_S_H
#define BLOCK_S_H
#include "block.h"
#include "position.h"
#include <vector>

/* 
   012
   ---
 0|
 1|
 2| SS
 3|SS

*/

class BlockS final: public Block {
  public:
  BlockS();
  ~BlockS();
};

#endif
