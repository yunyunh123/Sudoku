#include "Grid.h"

Grid::Grid(vector<int> gridnums) {
  grid.resize(size);
  int num; 
  bool fixed;
  for(int r = 0; r < size; r++) {
    //grid.at(r).resize(size); ??? creates error???
    for (int c = 0; c < size; c++) {
      num = gridnums.at(r*9+c);
      if (num == 0) {
        fixed = false;
      } else {
        fixed = true;
      }
      Box box(num, r, c, fixed);
      grid.at(r).push_back(box);
    }
  }
}

void Grid::update_grid(int fillnum, int r, int c) {
  grid.at(r).at(c).fillAns(fillnum);
}