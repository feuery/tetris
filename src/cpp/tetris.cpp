#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <Game.h>

using namespace std;

const int W = 800, H = 600;

int main(int argc, char** argh)
{
  Game game (W, H);
  if(game.initialized())
    game.Run();

  return 0;
}
