#include <Blocks.h>
#include <iostream>

using namespace std;

string Block::toString()
{
  string toret = "[";
  for(int x=0;x<Width(); x++)
    {
      toret += "[";
      for(int y=0; y<Height(); y++)
	{
	  toret += (elementAt(x,y)?"true":"false");
	  toret += ", ";
	}
      toret += "],\n";
    }
  return toret +"]";
}

int  Block::Width()
    {
      return W;
    }

  int  Block::Height()
  {
    return H;
  }
  
Block::Block(int W, int H): W(W), H(H)
{
  for(int x=0;x<W;x++)
    {
      Blockrow row(H);
      vertical_rows.push_back(row);
    }
}

Block::Block(int W, int H, vector<vector<bool>> values): W(W), H(H)
{
  for(int x=0; x<W; x++)
    {
      Blockrow row(H);
      for(int y=0; y<H; y++)
	try
	  {
	    row.data.get()[y] = values.at(x).at(y);
	  }
	catch(out_of_range ex)
	  {
	    cout<<"Trying to read at values.at("<<x<<").at("<<y<<"), when values.size is "<<values.size()<<" and values.at(x).size() is "<<values.at(x).size()<<endl;
	  }
      vertical_rows.push_back(row);
    }
}

bool Block::elementAt(int x, int y)
{
  // try
  //   {
      return vertical_rows.at(x).elementAt(y);
  //   }
  // catch(out_of_range ex)
  //   {
  //     cout<<"Out of range@ Block::elementAt(int,int)"<<endl;
  //     cout<<"x & width: " << x<<", "<<vertical_rows.size()<<endl;
  //     throw ex;
  //   }
}

Block Block::set(int x, int y, bool value)
{
  Block toret(W,H);
  toret.vertical_rows = vertical_rows; //Hopefully this result's in a copy...

  toret.vertical_rows.at(x).data.get()[y] = value; 

  return toret; //And this hopefully copies the local object instead of returning garbage
}

Block Block::merge(Block other, int x, int y)
{
  Block toret(W, H);
  toret.vertical_rows = vertical_rows;

  for(int local_x=x; local_x < x + other.W; x++)
    {
      for(int local_y=0; local_y < y + other.H; y++)
	{
	  toret = toret.set(local_x, local_y,
			    other.elementAt(local_x-W, local_y-H));
	}
    }

  return toret;    
}

//Callers are expected to free these surfaces after every frame
SDL_Surface* Block::Render()
{
  Uint32 rmask, gmask, bmask, amask;
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface* toret = SDL_CreateRGBSurface(0, 50*W,50*H, 32, rmask, gmask, bmask, amask); 

    for(int x=0; x < W; x++)
      {
	for(int y=0; y < H; y++)
	  {
	    SDL_Rect rect = {x * 50 +5, y * 50 + 5, 40, 40};
	    SDL_FillRect(toret, &rect,
			 elementAt(x,y)?
			 SDL_MapRGB(toret->format, 255, 0, 0) :
			 SDL_MapRGB(toret->format, 0, 0, 255)
			 ); //@TODO: Write custom colours for each block...
	  }
      }

    return toret;
}
