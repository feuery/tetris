#include <World.h>

World::World(int W, int H)
{
  world = new bool*[W];
  for(int x=0; x<W;x++)
    world[x] = new bool[H];
}

World::~World()
{
  delete[] world;
}

bool World::elementAt(int x, int y)
{
  return world[x][y];
}
