#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <blockrow.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

using namespace std;

class Block{
public:
  Block(int W, int H);

  Block(int W, int H, vector<vector<bool>> values);
  
  bool elementAt(int x, int y);
  //Should be not-destructive
  //But, if I'm wrong, we'll get funny bugs in the future
  Block set(int x, int y, bool value);

  Block merge(Block other, int x, int y);

  SDL_Surface* Render();

  bool Current_Block = false;

  int Width();
  int Height();
  
private:
  vector<Blockrow> vertical_rows;
  int W, H;
  
};

#endif //BLOCKS_H
