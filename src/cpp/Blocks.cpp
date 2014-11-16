#include <Blocks.h>
#include <iostream>

using namespace std;

Block::Block(int W, int H): W(W), H(H)
{
  for(int x=0;x<W;x++)
    {
      cout<<"In Block::Block(int, int); W is "<<W<<endl;
      
      Blockrow row(H);
      cout<<"Row("<<H<<") allocated"<<endl;
      vertical_rows.push_back(row);

      cout<<"Row("<<H<<") pushed_back()"<<endl;
    }

  cout<<"Leaving Block::Block"<<endl;
}

Block::Block(int W, int H, vector<vector<bool>> values): W(W), H(H)
{
  for(int x=0; x<W; x++)
    {
      Blockrow row(H);
      for(int y=0; y<H; y++)
	row.data[y] = values.at(x).at(y);
    }
}

bool Block::elementAt(int x, int y)
{
  return vertical_rows.at(x).elementAt(y);
}

Block Block::set(int x, int y, bool value)
{
  Block toret(W,H);
  toret.vertical_rows = vertical_rows; //Hopefully this result's in a copy...

  toret.vertical_rows.at(x).data[y] = value; 

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

    SDL_Surface* toret = SDL_CreateRGBSurface(0, 50,50, 32, rmask, gmask, bmask, amask); 

    for(int x=0; x < W; x++)
      {
	for(int y=0; y < H; y++)
	  {
	    SDL_Rect rect = {x * 50 +5, y * 50 + 5, 40, 40};
	    SDL_FillRect(toret, &rect, SDL_MapRGB(toret->format, 0, 0, 255)); //@TODO: Write custom colours for each block...
	  }
      }

	return toret;
}
