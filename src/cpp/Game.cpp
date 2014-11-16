#include <Game.h>
#include <iostream>

using namespace std;

Game::Game(int w, int h): W(w), H(h)
{
  cout<<"Initing everything"<<endl;
  if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
      fprintf(stderr, "Virhe %s\n", SDL_GetError());
      return;
    }
  atexit(SDL_Quit);

  window = SDL_CreateWindow("SDL-testi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
  if (window == nullptr)
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return;
    }

  this->window_surface = SDL_GetWindowSurface(this->window);
  running = true;
}

bool Game::initialized() const
{
  return running && window != nullptr && window_surface != nullptr;
}

Game::~Game()
{
  //You don't need to free the window_surface
  SDL_DestroyWindow(window);
}

void Game::Run()
{
  World world(W/50, H/50);
  while(initialized())
    {
      update(world);
      draw(window_surface, world);
      event_loop();
    }
}

void Game::update(World& world)
{
  // World-class functions
  // cout<< (world.elementAt(0,0)?"TRUUUE":"false :(") <<endl;
}

void Game::draw(SDL_Surface* window_surface, World& world)
{
  SDL_Rect rect = {100,100, 600,400};
  SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0xFF, 0,0));
  SDL_UpdateWindowSurface(window);
}

void Game::event_loop()
{
  SDL_Event e;

  while(SDL_PollEvent(&e))
    if(e.type == SDL_QUIT)
      {
	cout<<"Not running!"<<endl;
	running = false;
      }
}
