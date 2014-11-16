#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <blockrow.h>

using namespace std;

class Block{
public:
  Block(int W, int H);

  Block(int W, int H, vector<vector<bool>> values); //IE. not statically bounds-checked 2D-array
  
  bool elementAt(int x, int y);
  //Should be not-destructive
  //But, if I'm wrong, we'll get funny bugs in the future
  Block set(int x, int y, bool value); 
  
private:
  vector<Blockrow> vertical_rows;
  int W, H;
  
};

#endif //BLOCKS_H
