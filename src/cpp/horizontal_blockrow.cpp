#include <horizontal_blockrow.h>

Horizontal_Blockrow::Horizontal_Blockrow(int W, int H)
{
  for(int x=0;x<W;x++)
    {
      Blockrow row(H);
      data.push_back(row);
    }
}

bool Horizontal_Blockrow::elementAt(int x, int y)
{
  return vertical_rows.at(x).elementAt(y);
}
