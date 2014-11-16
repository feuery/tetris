#include <World.h>

World::World(int W, int H)
{
  data = new Block(W, H);
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
