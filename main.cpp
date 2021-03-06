// Copyright 2021 Julia Hua jhua2@bu.edu

#include <vector>
#include <time.h>
#include "Button.h"
#include "Grid.h"
#include <fstream>
#include <iostream>
using std::ifstream;
using std::vector;
using std::cout;

/* Boxes are numbered like so:
  0   1   2   3   4   5   6   7   8
  9  10  11  12  13  14  15  16  17
 18  19  20  21  22  23  24  25  26
  ...
 72  73  74  75  76  77  78  79  80
*/

int grid_size = 9; // length/width of grid, in terms of number of boxes
int box_size = 50; // length/width of each box, in terms of pixels
float gridPos = 25; // Position of top-left corner of grid, in terms of pixels
int probNum; // Number of problems stored in "problems.txt"
vector<int> filenums; // stores all numbers in "problems.txt"

sf::RenderWindow window(sf::VideoMode(675, 500), "Sudoku", sf::Style::Titlebar | sf::Style::Close);

// Reads a file that has Sudoku puzzles
void fileinput() {
  char c;
  int num;
  std::ifstream ifile("problems.txt");

  while (ifile >> c) {
    num = c - '0';
    filenums.push_back(num);
  }

  probNum = filenums.size() / 81;
}

// Chooses a random puzzle from filenums
vector<int> getPuzzle() {
  vector<int> gridnums;
  int probPicked;
  srand((unsigned)time(NULL));
  probPicked = rand() % probNum + 1; // random generator between 1 and probNum

  for (int i = (probPicked - 1) * 81; i < probPicked * 81; i++) {
    gridnums.push_back(filenums.at(i));
  }

  return gridnums;
}

int main() {

  // Get puzzle
  fileinput();
  vector<int> gridnums = getPuzzle();

  // Set up grid and buttons
  sf::Font arial;
  arial.loadFromFile("arial.ttf");

  Grid grid(gridnums, grid_size, box_size);
  grid.setPosition({gridPos, gridPos});

  vector<Button> btns;
  btns.clear();
  vector<string> str = {"New Game", "Restart", "Correct?", "Start Time"};

  for (int i = 0; i < 4; i++) {
    Button btn(str.at(i), {150, 50}, 20, sf::Color::Blue, sf::Color::White);
    btns.push_back(btn);
    btns.at(i).setPosition({500, static_cast<float>(gridPos + 100 * i)});
    btns.at(i).setFont(arial);
  }

  // Game loop
  bool startTime = false;;
  int x = 0, y = 0; // positions on grid

  timespec startT, endT;
  int sec;
  int min;
  int hr;
  char formattedT [9];

  while(window.isOpen()) {
    window.setFramerateLimit(60); // 60 frames per sec
    sf::Vector2i position = sf::Mouse::getPosition(window);

    // Event loop
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { // Window closed
        window.close();
      }

      if(event.type == sf::Event::MouseButtonPressed) { // Mouse event
        // Box selected
        if (event.mouseButton.button == sf::Mouse::Left) {
          x = position.x;
          y = position.y;
          grid.selectBox(x, y);
        }

        // Button(s) selected
        for (int i = 0; i < 4; i++) {
          // New Game
          if (btns.at(0).isMouseOver(window)) {
            vector<int> newgridnums = getPuzzle();
            grid.newGrid(newgridnums);
            grid.setPosition({gridPos, gridPos});
          }

          // Restart
          if (btns.at(1).isMouseOver(window)) {
            grid.resetGrid();
            btns.at(2).setText("Correct?");
            btns.at(3).setText("Start Time");
            startTime = false;
          }

          // Correct? : checks if puzzle is solved correctly
          if (btns.at(2).isMouseOver(window)) {
            if (grid.isCompleted() == true and grid.checkError() == true) {
              btns.at(2).setText("Congrats!");
            } else {
              btns.at(2).setText("No, Retry!");
            }
          }

          // Start Time
          if (btns.at(3).isMouseOver(window)) {
            startTime = true;
            clock_gettime(CLOCK_REALTIME, &startT);
          }
        }
      }

      // Changes color of buttons when mouse hovers over buttons
      if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < 4; i++) {
          if (btns.at(i).isMouseOver(window)) {
            btns.at(i).setBackColor(sf::Color(0, 191, 255));
          } else {
            btns.at(i).setBackColor(sf::Color::Blue);
          }
        }
      }

      // Text input
      if(event.type == sf::Event::TextEntered) {
        grid.userInput(event);
        vector<int> gridVals;
        gridVals = grid.getGrid();
      }
    }

    // Display time spent since button 3 was clicked
    if(startTime) {
      clock_gettime(CLOCK_REALTIME, &endT);
      sec = endT.tv_sec - startT.tv_sec;
      min = sec / 60;
      sec = sec % 60;
      hr = min / 60;
      min = min % 60;

      sprintf(formattedT, "%02d:%02d:%02d", hr, min, sec);
      btns.at(3).setText(formattedT);
    }

    // Redraw window
    window.clear();

    for (int i = 0; i < 4; i++) {
      btns.at(i).drawTo(window);
    }
    grid.drawGrid(window);
    grid.drawNums(window);
    window.display();
  }
}
