#ifndef HORIZONTAL_BLOCKROW_H
#define HORIZONTAL_BLOCKROW_H

#include <vector>
#include <blockrow.h>

using namespace std;

class Horizontal_Blockrow{
public:
  Horizontal_Blockrow(int W, int H);

  bool elementAt(int x, int y);
  
private:
  vector<Blockrow> vertical_rows;
  
};

#endif //HORIZONTAL_BLOCKROW_H
