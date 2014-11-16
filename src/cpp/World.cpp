#include <World.h>
#include <iostream>

using namespace std;

World::World(int W, int H)
{
  cout<<"In World::World(int, int)"<<endl;
  data = new Block(W, H);
  cout<<"Leaving World::World(int, int)"<<endl;
}

World::~World()
{
  delete data;;
}

bool World::elementAt(int x, int y)
{
  return data->elementAt(x,y);
}

void World::merge(Block block, int x, int y)
{
  *data = data->merge(block, x, y);
}
