#pragma
#include "Box.h"
#include <vector>
using std::vector;

const int size = 9;

class Grid {
public:
  Grid(vector<int> gridnums);
  // bool on_grid(int x, int y);
  void update_grid(int fillnum, int r, int c);
  // void clear(); //empties grid, new game?
  vector<vector<Box>> grid;
private:

};

