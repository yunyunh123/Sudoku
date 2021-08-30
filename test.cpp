#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

using std::vector;
using std::cout;


int main() {


  int gridSize = 16;
int size_sqrt = 4;

  vector<int> boxInd;
  boxInd.resize(gridSize);
  int ind = 0;

  for (int i = 0; i < size_sqrt; i ++ ) {
    for (int j = 0; j < size_sqrt; j++) {
      boxInd.at(ind) = i * size_sqrt + gridSize * size_sqrt * j;
      ind++;
    }
  }

  for (auto i : boxInd)
    cout << i << " ";


  return 0;
}