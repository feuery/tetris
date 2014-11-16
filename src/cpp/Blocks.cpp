#include <Blocks.h>

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
