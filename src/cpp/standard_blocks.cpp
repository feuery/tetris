#include <standard_blocks.h>

template <size_t w, size_t h>
vector<vector<bool>> toVector(bool (&arr)[w][h])
{
  vector<vector<bool>> toret;
  for(unsigned int x=0;x<w;x++)
    {
      vector<bool> row;
      for(unsigned int y=0; y<h; y++)
	{
	  row.push_back(arr[x][y]);
	}
      toret.push_back(row);
    }

  return toret;
}

Block standard_blocks:: get_standard_block(int n)
{/*
	[[[0 1]
	[1 1]
	[1 0]]

	[[1 0]
	[1 1]
	[0 1]]

	[[1]
	[1]
	[1]]

	[[1 1]
	[1 1]]

	[[1 0]
	[1 0]
	[1 1]]

	[[0 1]
	[0 1]
	[1 1]]] */
  if(blocks.size()==0)
    {
      bool eka[][3] = {
	{false,
	 true,
	 true},
	     {true,
	      true,
	      false}};

      bool toka[][3] =
	{{true,
	  true,
	  false},
	          {false,
		  true,
		  true}};
      bool kolmas [][1] =
	{{true},
	 {true},
	 {true}};

      bool neljas [2][2] =
	{{true,
	  true},
	 {true,
	  true}};
      bool viides [][3] =
	{{true,
	  true,
	  true},
	 {false,
	  false,
	  true}};

      bool kuudes [][3] =
	{{false,
	  false,
	  true},
	 {true, true, true}};

      blocks.push_back(Block(2,3, toVector(eka)));
      blocks.push_back(Block(2,3, toVector(toka)));
      blocks.push_back(Block(1,3, toVector(kolmas)));
      blocks.push_back(Block(2,2, toVector(neljas)));

      blocks.push_back(Block(2,3, toVector(viides)));
      blocks.push_back(Block(2,3, toVector(kuudes)));
    }

  return blocks.at(n);
}
