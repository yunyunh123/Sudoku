#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

using std::vector;
using std::cout;


int size = 9;

int main() {

  int size_sqt = sqrt(size);
  vector<int> test;
  vector<int> box;
  box.resize(size);

  for (int i  = 0; i < size_sqt; i++) {
    for (int j = 0; j < size_sqt; j++){
      test.push_back(i*size_sqt + size * size_sqt * j);

    }
  }



  int i = 0;
  for (auto start : test) {

    for (int k = 0 ; k < size_sqt; k++){
      for (int d = 0; d < size_sqt; d++) {
        box.at(i) = start + k + d * size;
        i++;
      }
    }


    for (auto j: box) {
      cout << j << " ";
    }

    cout << "\n";

    i = 0;
  }



  

  return 0;
}