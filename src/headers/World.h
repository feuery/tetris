#ifndef WORLD_H
#define WORLD_H

//Take this class always as a reference&, because copying it dumps core for reasons known only to elder C++ gods...
class World{
public:
  World(int W, int H); //In tiles
  ~World();

  bool elementAt(int x, int Y);
  
private:
  bool** world;
};

#endif //WORLD_H
