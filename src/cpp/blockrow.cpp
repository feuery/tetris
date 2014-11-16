#include <blockrow.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Blockrow::Blockrow(int length): length(length)
{
  cout<<"At Blockrow(int)"<<endl;

  //Make data into some sort of smart pointer....
  //To quote facebook:
  /* luokka.data on taulukko heapissa + stackoliot jakavat tämän pointterin
     => looppiolion tippuessa scopesta kutsutaan destruktoria, joka vapauttaa tämän taulukon
     => \o/
   */
  
  data = new bool[length];
}

Blockrow::~Blockrow()
{
  cout<<"At ~Blockrow"<<endl;
  cout<<(disposed? "Tää on jo disposioitu, mitä sie teet pöljä?": "Not disposed yet")<<endl;
  delete[] data;

  disposed = true;
}

bool Blockrow::elementAt(int at)
{
  if(at>=length) throw out_of_range(string("Tyhmä! Älä lue yli ") + std::to_string(at) +":n!");
  return data[at];
}
