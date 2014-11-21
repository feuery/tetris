#include <Game.h>
#include <iostream>

using namespace std;

Game::Game(int w, int h): W(w), H(h), lastUpdated(0)
{
  cout<<"Initing everything"<<endl;
  if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
      fprintf(stderr, "Virhe %s\n", SDL_GetError());
      return;
    }

  window = SDL_CreateWindow("SDL-testi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
  if (window == nullptr)
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return;
    }

  if(TTF_Init() == -1)
    {
      printf("TTF_Init: %s\n", TTF_GetError());
      return;
    }
  
  this->window_surface = SDL_GetWindowSurface(this->window);
  //@TODO fix this to be ./DejaVuSans.ttf in the released version...
  font = TTF_OpenFont("/home/feuer/tetris/bin/DejaVuSans.ttf", 16);

  if(!font)
    {
      printf("Loading font failed");
      return;
    }
  
  atexit(SDL_Quit);
  atexit(TTF_Quit);
  running = true;


  
  cout<<"Inited successfully"<<endl;
}

bool Game::initialized() const
{
  return running && window != nullptr && window_surface != nullptr && font;
}

Game::~Game()
{
  //You don't need to free the window_surface
  TTF_CloseFont(font);
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
  if((SDL_GetTicks() - lastUpdated) > 1000)
    {
      world.MoveDown();
      world.handleFullRows();
      lastUpdated = SDL_GetTicks();
    }
  if((SDL_GetTicks() - keysLastUpdated) > 200)
    {
      if(leftDown) world.MoveLeft();
      if(rightDown) world.MoveRight();
      if(downDown) world.DropDown();
      if(upDown) world.RotateCurrent();
      keysLastUpdated = SDL_GetTicks();
    }
      
}

void Game::draw(SDL_Surface* window_surface, World& world)
{
  SDL_FillRect(window_surface, NULL, 0);
  
  SDL_Surface* world_image = world.Render();

  int half_w = W/2;
  int x = half_w - world_image->w / 2;
  
  SDL_Rect rect = {x, 0, 0, 0};
  
  SDL_BlitSurface(world_image, NULL, window_surface, &rect);

  // cout<<world.toString()<<endl; @TODO: A verbose - flag?
  
  SDL_UpdateWindowSurface(window);

  SDL_FreeSurface(world_image);
}

void Game::event_loop()
{
  SDL_Event e;

  while(SDL_PollEvent(&e))
    switch(e.type)
      {
      case SDL_QUIT:
	cout<<"Not running!"<<endl;
	running = false;
	break;
      case SDL_KEYDOWN:
	switch(e.key.keysym.sym)
	  {
	  case SDLK_LEFT:
	    leftDown = true;
	    break;
	  case SDLK_RIGHT:
	    rightDown = true;
	    break;
	  case SDLK_UP:
	    upDown = true;
	    break;

	  case SDLK_DOWN:
	    downDown = true;
	    break;
	  }
	break;
      case SDL_KEYUP:
	switch(e.key.keysym.sym)
	  {
	  case SDLK_LEFT:
	    leftDown = false;
	    break;
	  case SDLK_RIGHT:
	    rightDown = false;
	    break;
	  case SDLK_UP:
	    upDown = false;
	    break;
	  case SDLK_DOWN:
	    downDown = false;
	  }
	break;
      }
}
