#ifndef BLOCKROW_H
#define BLOCKROW_H

class Blockrow{
public:
  Blockrow(int length);
  bool elementAt(int at);
  ~Blockrow();
private:

  int length;
  bool* data;

};

#endif //BLOCKROW_H
