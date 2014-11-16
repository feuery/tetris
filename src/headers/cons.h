#ifndef CONS_H
#define CONS_H

template <class H, class T>
class Cons{
public:
  Cons(H head, T tail);

  H Head();
  T Tail();
private:

  H head;
  T tail;
};

#endif //CONS_H
