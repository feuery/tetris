#include <blockrow.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Blockrow::Blockrow(int length): length(length), data(new bool[length] {false}){ }
  

bool Blockrow::elementAt(int at)
{
  if(at>=length) throw out_of_range(string("Tyhmä! Älä lue yli ") + std::to_string(at) +":n!");
  return data.get()[at];
}
