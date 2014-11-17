#include <SDL.h>
// #include <SDL2_gfxPrimitives.h>
#include <Game.h>

#include <cstdlib>
#include <ctime>

using namespace std;

const int W = 800, H = 600;

int main(int argc, char** argh)
{
  srand(time(NULL));
  
  Game game (W, H);
  if(game.initialized())
    game.Run();

  return 0;
}
