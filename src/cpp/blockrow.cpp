#include <blockrow.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Blockrow::Blockrow(int length): length(length), data(new bool[length] {false}){ }
  

bool Blockrow::elementAt(int at)
{
  if(at>=length) throw out_of_range(string("Tyhmä! Älä lue yli ") + std::to_string(at) +":n!\nMaksimi-indeksi on "+to_string(length-1));
  try
    {
  return data.get()[at];
    }
  catch(out_of_range ex)
    {
      cout<<"Mitä täällä tapahtuu?"<<endl;
      throw ex;
    }
}
