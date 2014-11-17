#ifndef WORLD_H
#define WORLD_H

#include <Blocks.h>

//Take this class always as a reference&, because copying it dumps core for reasons known only to elder C++ gods...
class World{
public:
  World(int W, int H); //In tiles
  ~World();

  bool elementAt(int x, int Y);

  //Destuctive
  void merge(Block block, int x, int y);

  SDL_Surface* Render();
  string toString()
  {
    return data->toString();
  }

  void MoveDown();
  void MoveLeft();
  void MoveRight();
private:
  Block* data;
  Block current_block;

  int current_x = 0, current_y = 0;
  
};

#endif //WORLD_H
