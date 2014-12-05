#include <blockrow.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Blockrow::Blockrow(int length): length(length), data(new bool[length] {false})
{
	for (int x = 0; x < length; x++)
	{
		data.get()[x] = false; //Initializers are broken in Visual C++13
	}
}  

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

template<typename T>
T* reverse_string(T *str, size_t len)
{
    T temp;
    len--;
    size_t stop = len/2;
    size_t i,k;

    for(i = 0, k = len; i < stop; i++, k--)
    {
    	temp = str[k];
    	str[k] = str[i];
    	str[i] = temp;
    }
    return str;
}

void Blockrow::Reverse()
{
  bool* newData = new bool[length];
  for(int i =0; i<length; i++)
    {
      newData[i] = data.get()[length-i];
    }

  data = shared_ptr<bool>(newData);
}

void Blockrow:: dropAt(int y)
{
  //Siirretään kaikkea <= y:n yhdellä eteenpäin?

  for(; y>0; y--)
    {
      data.get()[y] = data.get()[y-1];
    }
  data.get()[y] = false;
}
