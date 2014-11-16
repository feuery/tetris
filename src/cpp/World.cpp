#include <World.h>
#include <standard_blocks.h>

#include <iostream>
#include <cstdlib>

using namespace std;

standard_blocks b;

double RAND(double min, double max)
{
    return (double)rand()/(double)RAND_MAX * (max - min) + min;
}

World::World(int W, int H): data(new Block(W, H)), current_block( b.get_standard_block(RAND(0, b.count())))
{
  current_block.Current_Block = true;
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

SDL_Surface* World::Render()
{
  SDL_Surface* world_surface = data->Render();
  SDL_Surface* current_surface = current_block.Render();

  SDL_Rect current_location = {current_x * 50, current_y * 50, 0, 0};

  SDL_BlitSurface(current_surface, NULL, world_surface, &current_location);

  SDL_FreeSurface(current_surface);
  
  return world_surface;
}

