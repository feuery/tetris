#ifndef STANDARD_BLOCKS_H
#define STANDARD_BLOCKS_H

#include <vector>
#include <Blocks.h>
using namespace std;

//These should probably be hanging outside a class, but I can't bother to find out what syntax that system uses...
class standard_blocks
{
private:
  vector<Block> blocks;

public:
  Block get_standard_block(int n);
  int count();
};

#endif //STANDARD_BLOCKS_H
