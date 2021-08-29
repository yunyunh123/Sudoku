#pragma
#include "Box.h"
#include <vector>
#include <iostream>
using std::vector;

const int size = 9;

class Grid {
public:
  Grid(vector<int> gridnums, int gridSize, int boxSize);
  ~Grid();
  void setPosition(sf::Vector2f pos);
  // bool on_grid(int x, int y);
  void newGrid(vector<int> gridnums);
  void updateGrid(int fillnum, int boxnum);
  // void clear(); //empties grid, new game?
  void resetGrid();
  void drawGrid(sf::RenderWindow &window);
  void drawNums(sf::RenderWindow &window);
  void selectBox(int mouseX, int mouseY);
  void userInput(sf::Event input);
  vector<int> getGrid();
  bool checkError();
  bool isCompleted();
private:
  // Private functions
  bool repeatedVal(vector<int> boxes);

  vector<Box*> grid;
  //vector<int> gridValues;
  float pos_GridX;
  float pos_GridY;
  int gridSize;
  int boxSize;
  int selBox = -1;
  sf::Font font; 
};

