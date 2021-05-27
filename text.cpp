#include<iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <time.h>
using std::vector;
using std::string;
using std::cout;

int main() {

  clock_t t;
  int min = 0;
  int sec = 0;
  while (min < 1000) {
    t = clock();
    sec = stoi(std::to_string(t)) / 1000;
    min = sec / 60;
    sec = sec % 60;
    printf("%2d:%2d\n", min, sec );
  } 

}