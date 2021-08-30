#include "Grid.h"

// Constructor and Destructor
Grid::Grid(vector<int> gridnums,int gridS, int boxS) {
  gridSize = gridS;
  boxSize = boxS;

  int num = 0 ; 
  bool fixed;

  for(int i = 0; i < gridSize * gridSize; i++) {
      num = gridnums.at(i);

      if (num == 0) {
        fixed = false;
      } else {
        fixed = true;
      }
      
      grid.push_back(new Box(num, fixed));
  }
}

Grid::~Grid() {
  for (auto ele : grid) {
    delete ele;
  }
}

// Set up grid
void Grid::setPosition(sf::Vector2f pos) {
  // Sets position of the grid's upper-right corner
  pos_GridX = pos.x;
  pos_GridY = pos.y;

  // Sets position of the boxes
  float pos_BoxX = 0, pos_BoxY = 0;
  for (int i = 0; i < gridSize * gridSize; i++) {
    pos_BoxX = pos_GridX + 12 + ((i % gridSize) * boxSize);
    pos_BoxY = pos_GridY + ((i / gridSize) * boxSize);

    grid.at(i)->setPosition({pos_BoxX, pos_BoxY});
  }
}

void Grid::drawGrid(sf::RenderWindow &window) {
  float posX = 0;
  float posY = 0;

  for (int i = 0; i < gridSize * gridSize; i++) {
    posX = pos_GridX + ((i % gridSize) * boxSize);
    posY = pos_GridY + ((i / gridSize) * boxSize);

    // Individual boxes
    sf::RectangleShape square(sf::Vector2f(boxSize, boxSize));
    square.setPosition(posX, posY);
    square.setOutlineThickness(2);
    square.setOutlineColor(sf::Color(172,172,172));

    // Selected box is gray. Otherwise, it is white.
    if (selBox == i and grid.at(i)->isFixed() == false) {
      square.setFillColor(sf::Color(122, 141, 204));
    } else {
      square.setFillColor(sf::Color::White);
    }

    window.draw(square);
  }

  // Thickening lines to emphasize 3x3 squares
  int size_sqrt = sqrt(gridSize);

  for (int j = 0; j < 4; j++) { // Horizontal lines
    sf::RectangleShape line(sf::Vector2f(boxSize * gridSize, 4));
    line.setPosition(pos_GridX, pos_GridY + j * boxSize * size_sqrt);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }

  for (int j = 0; j < 4; j++) { // Vertical lines
    sf::RectangleShape line(sf::Vector2f(4, boxSize * gridSize));
    line.setPosition(pos_GridX + j * boxSize * size_sqrt, pos_GridY);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }
}

void Grid::drawNums(sf::RenderWindow &window) {
  font.loadFromFile("arial.ttf");

  for (int i = 0; i < gridSize * gridSize; i++) {
    (grid.at(i))->setFont(font);
    (grid.at(i))->drawTo(window);
  }
}

void Grid::newGrid(vector<int> gridnums) {
  for (auto ele : grid) {
    delete ele;
  }

  grid.clear();
  int num;
  bool fixed;

  for(int i = 0; i < gridSize * gridSize; i++) {
      num = gridnums.at(i);

        if (num == 0) {
          fixed = false;
        } else {
          fixed = true;
        }
        
        grid.push_back(new Box(num, fixed));
  }

  selBox = -1;
}

void Grid::updateGrid(int fillnum, int boxnum) {
  grid.at(boxnum)->fillAns(fillnum);
}

void Grid::resetGrid() {
  for (int i = 0; i < gridSize * gridSize; i++) {
    if (grid.at(i)->isFixed() == false) {
      grid.at(i)->clearAns();
    }
  }
}

void Grid::selectBox(int mouseX, int mouseY) {
  int boxnum, r, c;

  // Checks if mouse is within bounds
  // If so, box number can be determined
  if (mouseX >= 25 and mouseX <= 475
    and mouseY >= 25 and mouseY <= 475) {

    c = (mouseX - pos_GridX) / boxSize;
    r = (mouseY - pos_GridY) / boxSize;

    boxnum = r * gridSize + c;
    
    if (selBox != -1){ // no box selected
      grid.at(selBox)->select(false);
    }

    selBox = boxnum;
    grid.at(selBox)->select(true);
  }
}

void Grid::userInput(sf::Event input) {
  if(selBox != -1) {
    grid.at(selBox)->enterText(input);
  }
}

vector<int> Grid::getGrid() {

  vector<int> gridValues;
  gridValues.resize(81);

  for (int i = 0; i < gridSize * gridSize; i++) {
    gridValues.at(i) = grid.at(i)->num;
  }

  return gridValues;
}

bool Grid::checkError() {

  vector<int> gridValues = getGrid();
  vector<int> rowValues;
  vector<int> colValues;
  vector<int> boxValues;

  rowValues.resize(gridSize);
  colValues.resize(gridSize);
  boxValues.resize(gridSize);

  for (int i = 0; i < gridSize; i++) {
    // Check every row for repeated values
    for (int j = 0; j < gridSize; j++) { // Obtains row values
      rowValues.at(j) = gridValues.at(i * 9 + j);
    }

    if (repeatedVal(rowValues) == false) {
      std::cout << "Error row: " << i << std::endl;
      return false;
    }

    // check every column for repeated values
    for (int j = 0; j < gridSize; j++) { // Obtains column values
      colValues.at(j) = gridValues.at(i + j * gridSize);
    }

    if (repeatedVal(colValues) == false) {
      std::cout << "Error col: " << i << std::endl;
      return false;
    }
  }

  /* Check every box for repeated values:
      - Find indices of top-left box of every 3x3 square, store into boxInd
      - Use boxInd to find all 9 indices of every 3x3 square
  */
  int size_sqrt = sqrt(gridSize);
  vector<int> boxInd;
  boxInd.resize(gridSize);
  int ind = 0;
  for (int i = 0; i < size_sqrt; i ++ ) {
    for (int j = 0; j < size_sqrt; j++) {
      boxInd.at(ind) = i * size_sqrt + gridSize * size_sqrt * j;
      ind++;
    }
  }

  ind = 0;
  for (auto i : boxInd) {
    // Obtains all values in a 3x3 square
    for (int j = 0; j < size_sqrt; j++) {
      for (int k = 0; k < size_sqrt; k++){
        boxValues.at(ind) = gridValues.at(i + j + k * gridSize);
        ind++;
      }
    }

    ind = 0;

    if (repeatedVal(boxValues) == false) {
      std::cout << "Error box" << std::endl;
      return false;
    }
  }

  return true;
}

bool Grid::isCompleted() {
  vector<int> gridValues = getGrid();

  for (auto i : gridValues) {
    if (i == 0) {
      return false;
    }
  }

  return true;
}

bool Grid::repeatedVal(vector<int> boxes) {

  std::map<int,int> values;
  vector<int> error;

  for (auto i : boxes) { // Creates a map of all numbers in "boxes"
    auto it = values.find(i);

    if (it != values.end()) { // found value
      values.at(i)++;
    } else { // did not find value
      values.emplace(i, 1);
    }
  }

  for (auto ele : values) { // Checks if map has repeated values
    if (ele.first != 0) { // Box is not empty
      if (ele.second > 1) { // Repeated value
        return false;
      }
    }
  }

  return true;
}