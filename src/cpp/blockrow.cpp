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


void Blockrow::Reverse()
{
  bool* old_data = data.get();
  bool* new_data = new bool[length];
  
  int new_index = 0;
  for(int old_index = length-1; old_index >= 0; old_index--, new_index++)
    {
      printf("new_data[%d] = old_data[%d] = %s\n", new_index, old_index, old_data[old_index]?"true": "false");
      new_data[new_index] = old_data[old_index];
    };

  data = shared_ptr<bool>(new_data);

  for(int i=0; i<length; i++)
    {
      printf("At old_data, at %dth index, value is %s\n", i, old_data[i]?"true":"false");
      printf("Whereas at data, value is %s\n", data.get()[i]?"true":"false");
    }

  printf("REVERSED!\n");
}
