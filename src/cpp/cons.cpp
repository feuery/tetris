#include <cons.h>

template <class H, class T>
Cons<H, T>::Cons(H Head, T Tail): head(Head), tail(Tail) { }

template <class H, class T>
H Cons<H, T>::Head() { return head; }

template <class H, class T>
T Cons<H, T>::Tail() { return tail; }
