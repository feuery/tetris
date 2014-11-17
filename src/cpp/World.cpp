#include <World.h>
#include <standard_blocks.h>

#include <iostream>
#include <cstdlib>

#include <vector>
#include <algorithm>

using namespace std;

//inclusive, [start, end]
vector<int> range(int start, int end)
{
  vector<int> toret;

  for(int i=start; i<=end; i++)
    {
      toret.push_back(i);
    }
  return toret;
}

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
  
  return  world_surface;		
}

vector<vector<int>> ZipVectors(vector<int> first, vector<int> second)
{
  
}

bool World::newBlockRequired()
{
  int world_height = data->Height(),
    block_lowest_y = current_y + current_block.Height();
  
  bool atBottom = block_lowest_y >= world_height;

  vector<int> interesting_xs = range(current_x, current_x + current_block.Width());
  
  vector<int> interesting_ys (interesting_xs.size(), 0);
  
  transform(interesting_xs.begin(), interesting_xs.end(), interesting_ys.begin(),
	    [&](int x) ->
	    {
	      for(int y = current_block.Height()-1; y>-1; y--)
		{
		  if(current_block.elementAt(x, y)) return y + 1;
		}
	      return -1;
	    });
  
  // naitetaan xs ja ys [[x y] [x y]] - pareiksi
  // filtteröidään pois ne, joiden y == -1
  // lisätään jokaiseen x:ään current_x
  // lisätään jokaiseen y:hyn current_y
  // tarkistetaan World::elementAt:llä onko yksikään koordinaattipareista true?
}

void World::MoveDown()
{

  if() current_y++;
}

void World::MoveLeft()
{
  if(current_x > 0)
    current_x--;
}

void World::MoveRight()
{
  if(current_x + current_block.Width() < data->Width())
    current_x++;
}
