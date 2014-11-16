#include <blockrow.h>
#include <string>
#include <stdexcept>

using namespace std;

Blockrow::Blockrow(int length): length(length)
{
  data = new bool[length];
}

Blockrow::~Blockrow()
{
  delete[] data;
}

bool Blockrow::elementAt(int at)
{
  if(at>=length) throw out_of_range(string("Tyhmä! Älä lue yli ") + std::to_string(at) +":n!");
  return data[at];
}
