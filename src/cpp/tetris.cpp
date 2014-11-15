#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>

using namespace std;

const int W = 800, H = 600;

bool init_everything()
{
  cout<<"Initing everything"<<endl;
  if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
      fprintf(stderr, "Virhe %s\n", SDL_GetError());
      return false;
    }
  atexit(SDL_Quit);
  return true;
}

/**
 * Return the window surface...
 */
SDL_Surface* GetWindowAndRenderer(SDL_Window** window)
{
  // if(SDL_CreateWindowAndRenderer(W,H, 0, &window, &renderer) != 0)
  //   {
  //     fprintf(stderr, "Virhe: %s\n", SDL_GetError());
  //     return false;
  //   }

  *window = SDL_CreateWindow("SDL-testi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
  if (*window == nullptr)
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return nullptr;
    }

  return SDL_GetWindowSurface(*window);
}

int main(int argc, char** argh)
{
  if(!init_everything()) return -1;

  SDL_Window *window = nullptr;
  SDL_Surface *window_surface = nullptr;
  if((window_surface = GetWindowAndRenderer(&window)) == nullptr) return -1;
    

  bool running = true;

  cout<<"Going to loop"<<endl;
  while(running)
    {
      SDL_Rect rect = {100,100, 600,400};
      SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0xFF, 0,0));
      SDL_UpdateWindowSurface(window);

      SDL_Event e;

      while(SDL_PollEvent(&e))
	if(e.type == SDL_QUIT)
	  {
	    cout<<"Not running!"<<endl;
	    running = false;
	  }
    }

  SDL_DestroyWindow(window);
}
