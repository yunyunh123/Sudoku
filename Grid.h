// Copyright 2021 Julia Hua jhua2@bu.edu

#pragma
#include "Box.h"
#include <vector>
#include <iostream>
#include <map>
#include <math.h>
using std::vector;

class Grid {
public:
  // Constructor/Destructor
  Grid(vector<int> gridnums, int gridSize, int boxSize);
  ~Grid();

  // Public functions
  void setPosition(sf::Vector2f pos);
  void drawGrid(sf::RenderWindow &window);
  void drawNums(sf::RenderWindow &window);
  void newGrid(vector<int> gridnums);
  void updateGrid(int fillnum, int boxnum);
  void resetGrid();
  void selectBox(int mouseX, int mouseY);
  void userInput(sf::Event input);
  vector<int> getGrid();
  bool checkError();
  bool isCompleted();
private:
  // Private functions
  bool repeatedVal(vector<int> boxes);

  // Private attributes
  vector<Box*> grid;
  float pos_GridX;
  float pos_GridY;
  int gridSize;
  int boxSize;
  int selBox = -1;
  sf::Font font; 
};

