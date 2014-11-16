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
  cout<<"At Game::Run()|W: "<<W<<endl;
  int width = 8; //(W/50) - 3;

  cout<<"JEEE"<<width<<endl;
  
  
  World world(width, H/50);
  cout<<"World is ready!"<<endl;
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
  SDL_Surface* world_image = world.Render();

  int half_w = W/2;
  int x = half_w - world_image->w / 2;
  
  SDL_Rect rect = {x, 0, 0, 0};
  
  SDL_BlitSurface(world_image, NULL, window_surface, &rect);
  
  SDL_UpdateWindowSurface(window);

  SDL_FreeSurface(world_image);
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
