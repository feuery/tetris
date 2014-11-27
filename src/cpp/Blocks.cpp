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
  try
    {
      return vertical_rows.at(x).elementAt(y);
    }
  catch(out_of_range ex)
    {
      cout<<"Out_of_range @ Block::elementAt"<<endl;
      throw ex;
    }
}

Block Block::set(int x, int y, bool value)
{
  Block toret(W,H);
  toret.vertical_rows = vertical_rows; //Hopefully this result's in a copy...

  toret.vertical_rows.at(x).data.get()[y] = value; 

  return toret; //And this hopefully copies the local object instead of returning garbage
}

/*
  printf("Looping... x,y = %d, %d @ Block::merge\n", local_x, local_y);
  printf("Values going to elementAt(%d, %d)\n", local_x, local_y-other.H);
*/

Block Block::merge(Block other, int x, int y)
{
  Block toret(W, H);
  toret.vertical_rows = vertical_rows;

  int otherx = 0;

  printf("Other block: %s\n", other.toString().c_str());
  
  for(int local_x = x; local_x < x + other.Width(); local_x++)
    {
      int othery = 0;
      for(int local_y = y; local_y < y + other.Height(); local_y++)
	{
	  if(!elementAt(local_x, local_y))
	    {
	      set(local_x, local_y, other.elementAt(otherx, othery));
	  
	      printf("Merging %s from (%d, %d) to (%d, %d)\n", other.elementAt(otherx, othery)? "true": "false",
		     otherx, othery,
		     local_x, local_y);
	    }
	  othery++;
	}
      otherx++;
    }
  printf("Blocks merged!");

  printf("World: %s\n, merged at (%d, %d)", toString().c_str(), x, y);

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
			    Current_Block?
			      SDL_MapRGB(toret->format, 255, 0, 0):
			      SDL_MapRGB(toret->format, 255, 255, 0):
			    Current_Block?
			      SDL_MapRGBA(toret->format, 0, 0, 0, 0):
			      SDL_MapRGB(toret->format, 0, 0, 255)
			    
			 ); //@TODO: Write custom colours for each block...
	  }
      }

    return toret;
}


bool Block::doesHorizontallyCollide_left(Block another, int x, int y) //World coords, not another-coords
{
  int low_x = x-1;

  if(low_x<0) return true;

  for(int local_y = y;local_y< y + another.Height(); local_y++)
    {
      bool value = elementAt(low_x, local_y);
      
      if(value) return true;
    }
  
  return false;
}

bool Block::doesHorizontallyCollide_right(Block another, int x, int y) //World coords, not another-coords
{
  int high_x = x + another.Width();

  if(high_x >= Width()) return true;

  for(int local_y = y ;local_y< y + another.Height(); local_y++)
    {
      if(elementAt(high_x, local_y)) return true;
    }

  return false;
}

template <typename T>
vector<T> reverse(vector<T> vec)
{
  vector<T> toret;

  for(auto iter = vec.end()-1; iter>= vec.begin(); iter--)
    {
      toret.push_back(*iter);
    }
  return toret;
}

Block Block::Rotate()
{
  Block toret(H, W);

  for(int x=0; x<W; x++)
    for(int y=0; y<H; y++)
      {
	toret.set(y,x, elementAt(x, y)); 
      }
  
  toret.Current_Block = Current_Block;
  toret.vertical_rows = reverse(toret.vertical_rows);
  return toret;
}

template <class BidirectionalIterator>
  void doReverse (BidirectionalIterator first, BidirectionalIterator last)
{
  while ((first!=last)&&(first!=--last)) {
    std::iter_swap (first,last);
    ++first;
  }
}

void Block::InsertFront()
{
  vector<Blockrow> data = vertical_rows;
  doReverse(data.begin(), data.end());
  data.push_back(Blockrow(H));
  doReverse(data.begin(), data.end());
  vertical_rows = data;
}

void Block::DropAt(int y)// vector<Blockrow>::iterator n)
{
  for(int x=0; x<W; x++)
    {
      printf("Dropping item at (%d, %d)\n", x, y);
      vertical_rows.at(x).dropAt(y);
    }
}

vector<Blockrow>::iterator Block::begin()
{
  return vertical_rows.begin();
}

bool Block::topContainsTile()
{
  for(int x=0; x<W; x++)
    {
      if(elementAt(x, 0)) return true;
    }
  return false;
}
