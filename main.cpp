// Copyright 2021 Julia Hua jhua2@bu.edu

#include <stdio.h> // take out
#include<vector>
#include<time.h>
#include "Button.h"
#include "Grid.h"
#include <time.h>
#include <fstream>
using std::ifstream;

using std::cin;
using std::stoi;
using std::vector;

int grid_size = 9; // length of each side of the grid (9x9)
int box_size = 50; // length of each side of the box
sf::RenderWindow window(sf::VideoMode(675, 500), "Sudoku", sf::Style::Titlebar | sf::Style::Close);
vector<int> filenums;
int probNum;

  /* 
  Boxes are numbered like this:

  0   1   2   3   4   5   6   7   8
  9  10  11  12  13  14  15  16  17
 18  19  20  21  22  23  24  25  26
  ...
 72  73  74  75  76  77  78  79  80
  */

int getBoxNum(int x, int y) {

  x = x - 25;
  y = y - 25;

  int row = x / 50;
  int col = y / 50;

  return grid_size * col + row;
}

void fileinput() {

 // gridnums.resize(81);
  char c;
  int num;
  int count = 0;
  std::ifstream ifile("problems.txt");
  while (ifile >> c) {
    num = c - '0';
    // error check if num is between 0 and 9
    filenums.push_back(num);
  }

  probNum = filenums.size()/81;


}

vector<int> getPuzzle() {
  vector<int> gridnums;
  int probPicked;

  srand((unsigned)time(NULL));
  probPicked = rand() % probNum + 1; // generator between 1 and probNum

  for (int i = (probPicked-1) * 81; i < probPicked * 81; i++) {
    gridnums.push_back(filenums.at(i));
  }

  return gridnums;

}



int main() {

  fileinput(); // get problem set
  vector<int> gridnums = getPuzzle();
  Grid grid(gridnums, grid_size, box_size);
  grid.setPosition({25,25});

  sf::Font arial;
  arial.loadFromFile("arial.ttf");

  vector<Button> btns;
  btns.clear();
  vector<string> str = {"New Game", "Restart", "Correct?", "Start Time"};
  //btns.resize(4);

  for (int i = 0; i < 4; i++) {
 
    Button btn(str.at(i), {150, 50}, 20, sf::Color::Blue, sf::Color::White);
    btns.push_back(btn);
    btns.at(i).setPosition({500, static_cast<float>(25 + 100 * i)});
    btns.at(i).setFont(arial);
  }


  int boxnum = 0;

  bool sel;
  bool startTime = false;;
  int x = 0, y = 0;

  timespec startT, endT;
  int sec;
  int min;
  int hr;
  char formattedT [9];



  while(window.isOpen()) {

    window.setFramerateLimit(60); // 60 frames per sec

    sf::Vector2i position = sf::Mouse::getPosition(window);

    sf::Event event;
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();

      if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left) {   
          x = position.x;
          y = position.y;
          grid.selectBox(x, y);
        }

        for (int i = 0; i < 4; i++) {
          if (btns.at(i).isMouseOver(window)) {
            std::cout << "You clicked button " << i << std::endl;
          }
          if (btns.at(0).isMouseOver(window)) {
            vector<int> newgridnums = getPuzzle();

            grid.newGrid(newgridnums);
            grid.setPosition({25,25});


          } 

          if (btns.at(1).isMouseOver(window)) { // restart
            grid.resetGrid();

            btns.at(3).setText("Start Time");
            startTime = false;
          }

          if (btns.at(2).isMouseOver(window)) {
            if (grid.isCompleted() == true) {
              
              if (grid.checkError() == true){
                btns.at(2).setText("Congrats!");
              } else {
                btns.at(2).setText("No, Retry!");
              }
            }
            else{
              btns.at(2).setText("No, Retry!");
            }
          }

          if (btns.at(3).isMouseOver(window)) {
            startTime = true;
            clock_gettime(CLOCK_REALTIME, &startT);
          }
        }
      }

      if(event.type == sf::Event::TextEntered) {
        grid.userInput(event);
        vector<int> gridVals;
        gridVals = grid.getGrid();

       }


      if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < 4; i++) {
          if (btns.at(i).isMouseOver(window)) {
            btns.at(i).setBackColor(sf::Color(0,191,255));
          }
          else {
            btns.at(i).setBackColor(sf::Color::Blue);
          }
        }

      }

    }

    window.clear();

    for (int i = 0; i < 4; i++) {
      btns.at(i).drawTo(window);
    }

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


    grid.drawGrid(window);


    grid.drawNums(window);

    window.display();

  }
}
