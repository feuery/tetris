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

  int score = 0;

  TTF_Font *font;

  Uint32 lastUpdated, keysLastUpdated = 0;

  bool leftDown = false, rightDown = false, upDown = false, downDown = false;
};

#endif //GAME_H
