#include "Grid.h"
#include <map>
#include <math.h>

Grid::Grid(vector<int> gridnums,int gridS, int boxS) {
  gridSize = gridS;
  boxSize = boxS;


  //grid.reserve(81); // 9*9 = 81
  int num = 0 ; 
  bool fixed;


  for(int i = 0; i < gridSize * gridSize; i++) {
    //std::cout << i << " " << num << std::endl;
      num = gridnums.at(i);
      //std::cout << i << " " << num << std::endl;

      if (num == 0) {
        fixed = false;
      } else {
        fixed = true;
      }
      
      grid.push_back(new Box(num, fixed));

  }

  //fprintf(stdout, "%lu", grid.size());

  //std::cout << "????"<< std::endl;

  // setting position of all the boxes (with text in it)
  //font.loadFromFile("arial.ttf"); // default font


}

Grid::~Grid() {
  for (auto ele : grid) {
    delete ele;
  }
}

void Grid::setPosition(sf::Vector2f pos) {
  //sets position of the grid's upper-right corner
  pos_GridX = pos.x;
  pos_GridY = pos.y;


  //set position of the boxes
  float pos_BoxX = 0, pos_BoxY = 0;
  for (int i = 0; i < gridSize * gridSize; i++) {
    pos_BoxX = pos_GridX + 12 + ((i % gridSize) * boxSize); // generalize the 12
    pos_BoxY = pos_GridY + ((i / gridSize) * boxSize);

    grid.at(i)->setPosition({pos_BoxX, pos_BoxY});
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
    //std::cout << i << " " << num << std::endl;
      num = gridnums.at(i);
      //std::cout << i << " " << num << std::endl;

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

//drawGrid??
void Grid::drawGrid(sf::RenderWindow &window) {
  float posX = 0;
  float posY = 0;

  for (int i = 0; i < gridSize * gridSize; i++) {
    posX = pos_GridX + ((i % gridSize) * boxSize);
    posY = pos_GridY + ((i / gridSize) * boxSize);

    sf::RectangleShape square(sf::Vector2f(boxSize, boxSize));
    square.setPosition(posX, posY);
    square.setOutlineThickness(2);
    square.setOutlineColor(sf::Color(172,172,172));

    if (selBox == i and grid.at(i)->isFixed() == false) {
      //std::cout << selBox << std::endl;
      square.setFillColor(sf::Color(122, 141, 204));
    } else {
      square.setFillColor(sf::Color::White);
    }

    window.draw(square);

  }

  // Horizontal lines
  for (int j = 0; j < 4; j++) {
    sf::RectangleShape line(sf::Vector2f(boxSize * gridSize, 4));
    line.setPosition(pos_GridX, pos_GridY + j * boxSize * 3);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }

  // Vertical Lines
  for (int j = 0; j < 4; j++) {
    sf::RectangleShape line(sf::Vector2f(4, boxSize * gridSize));
    line.setPosition(pos_GridX + j * boxSize * 3, pos_GridY);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }


}

void Grid::drawNums(sf::RenderWindow &window) {

  font.loadFromFile("arial.ttf");

  for (int i = 0; i < gridSize * gridSize; i++) {
    // if (!grid.at(i))
    // {
    //   std::cout << "it's null :<" << std::endl;
    //   continue;
    // }

     (grid.at(i))->setFont(font);

    (grid.at(i))->drawTo(window);
    //std::cout << "????"<< std::endl;
  }




}

void Grid::selectBox(int mouseX, int mouseY) {
  
  int boxnum, r, c;

  if (mouseX >= 25 and mouseX <= 475
    and mouseY >= 25 and mouseY <= 475) {

    c = (mouseX - pos_GridX) / boxSize;
    r = (mouseY - pos_GridY) / boxSize;

    boxnum = r * gridSize + c;
    

    //initially selBox is -1
    // if mouseX and mouseY is within bounds
    // boxnum should also be
    if (selBox != -1){
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

vector<int> Grid::getGrid() { // should this be a member of this class?? fillANs??

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

  rowValues.resize(gridSize); // length 9, stores current row values
  colValues.resize(gridSize);
  boxValues.resize(gridSize);
  //errors.clear();



  for (int i = 0; i < gridSize; i++) {
    // check every row for repeated values
    for (int j = 0; j < gridSize; j++) { // iterates through rowValues
      rowValues.at(j) = gridValues.at(i * 9 + j);
    }

    if (repeatedVal(rowValues) == false){
      std::cout << "Error row: " << i << std::endl;
      return false;
    }

    // // check if there's any repeated values
    // for (auto k : repeatedVal(rowValues)) {
    //   errorBoxNums.push_back(k);
    // }



    // check every column for repeated values
    for (int j = 0; j < gridSize; j++) {
      colValues.at(j) = gridValues.at(i + j * gridSize);
    }

    if (repeatedVal(colValues) == false){
      std::cout << "Error col: " << i << std::endl;
      return false;
    }
  }



  int size_sqrt = sqrt(gridSize);
  // box indices
  vector<int> boxInd;
  boxInd.resize(gridSize);
  int ind = 0;
  for (int i = 0; i < size_sqrt; i ++ ) {
    for (int j = 0; j < size_sqrt; j++) {
      boxInd.at(ind) = i * size_sqrt + size * size_sqrt * j;
      ind++;
    }
  }



  // check boxes
  ind = 0;
  for (auto i : boxInd) {

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

// example: 0 1 9 2 4 2 3 0 0 
// vector of 9 integers

  std::map<int,int> values;
  vector<int> error;
  vector<int> pos; // positions

  for (auto i : boxes) { // creates a map of all numbers in "boxes"

    auto it = values.find(i);

    if (it != values.end()) {
      // found value
      values.at(i)++;
    } else {
      // did not find value
      values.emplace(i, 1);
    }
  }

  for (auto ele : values) { // Checks if map has repeated values
    if (ele.first != 0) { // value is not 0 and thus between 1 and 9
      if (ele.second > 1) { // there is a number present more than 1 time 
        return false;
      }

    }
  }


  return true;


}