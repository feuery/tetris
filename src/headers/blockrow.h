#ifndef BLOCKROW_H
#define BLOCKROW_H

class Blockrow{
  friend class Block;
public:
  Blockrow(int length);
  bool elementAt(int at);
  ~Blockrow();  
  
private:

  int length;
  bool* data;

  bool disposed = false;

};

#endif //BLOCKROW_H
