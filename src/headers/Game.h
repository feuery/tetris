#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <World.h>
#include <SDL_ttf.h>

class Game
{
public:
  Game(int w, int h);
  void Run();

  bool initialized() const;
  
  ~Game();
  
private:
  void event_loop();
  void draw(SDL_Surface* window, World& world);
  void update(World& world);

  SDL_Surface* window_surface = nullptr;
  SDL_Window* window = nullptr;

  bool running = false;
  int W, H; //pixels

  TTF_Font *font;

  Uint32 lastUpdated;
};

#endif //GAME_H
