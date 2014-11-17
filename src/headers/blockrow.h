#ifndef BLOCKROW_H
#define BLOCKROW_H

#include <memory>

using namespace std;

class Blockrow{
  friend class Block;
public:
  Blockrow(int length);
  bool elementAt(int at);

  void Reverse(); //Destructive
  
private:

  int length;
  shared_ptr<bool> data;
};

#endif //BLOCKROW_H
