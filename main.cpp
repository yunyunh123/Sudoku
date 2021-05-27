// Copyright 2021 Julia Hua jhua2@bu.edu

#include <stdio.h> // take out
#include<vector>
//#include<SFML/Network.hpp>
#include "Textbox.h"
#include "Button.h"
#include "Grid.h"
#include <time.h>
#include <fstream>
using std::ifstream;

// using std::cout;
using std::cin;
using std::stoi;
using std::vector;
// using std::string;

int grid_size = 9; // length of each side of the grid (9x9)
int box_size = 50; // length of each side of the box
sf::RenderWindow window(sf::VideoMode(675, 500), "Sudoku", sf::Style::Titlebar | sf::Style::Close);


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


void draw(bool sel, int x, int y, int& boxnum) {

  float x_pos = 0;
  float y_pos = 0;

  for (int i = 0; i < grid_size * grid_size; i++) {
    x_pos = 25 + ((i % grid_size) * box_size);
    y_pos = 25 + ((i / grid_size) * box_size);

    // Grid
    sf::RectangleShape square(sf::Vector2f(box_size,box_size));
    square.setPosition(x_pos, y_pos);
    square.setOutlineThickness(2);
    square.setOutlineColor(sf::Color(172,172,172));

    if(sel and (x > x_pos and x < x_pos + 50) and (y > y_pos and y < y_pos + 50)) {
      square.setFillColor(sf::Color(122, 141, 204));
      boxnum = i;
    } else {
      square.setFillColor(sf::Color::White);
    }

    window.draw(square);
  }

  // Horizontal lines
  for (int j = 0; j < 4; j++) {
    sf::RectangleShape line(sf::Vector2f(box_size * grid_size, 4));
    line.setPosition(25, 25 + j * box_size * 3);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }

  // Vertical Lines
  for (int j = 0; j < 4; j++) {
    sf::RectangleShape line(sf::Vector2f(4, box_size * grid_size));
    line.setPosition(25 + j * box_size * 3, 25);
    line.setFillColor(sf::Color(172,172,172));
    window.draw(line);
  }
}

vector<int> fileinput() {
  vector<int> gridnums;

  char c;
  int num;
  int count = 0;
  std::ifstream ifile("easy.txt");
  while (ifile >> c) {
    num = c - '0';
    // error check if num is between 0 and 9
    gridnums.push_back(num);
  }
  return gridnums;

}

int main() {

  vector<int> gridnums = fileinput();
  Grid grid(gridnums);

  // sf::Texture bg;
  // sf::Sprite background;
  // if(!bg.loadFromFile("forest.jpg"))
  //   return -1;
  // background.setTexture(bg);

  sf::Font arial;
  arial.loadFromFile("arial.ttf");

  vector<Button> btns;
  btns.clear();
  vector<string> str = {"New Game", "Restart", "Solution", "Start Time"};
  //btns.resize(4);

  for (int i = 0; i < 4; i++) {
    // cout << "Here" << std::endl;
    //btns.at(i) = Button(str.at(i), {150, 50}, 20, sf::Color::Blue, sf::Color::White);
    Button btn(str.at(i), {150, 50}, 20, sf::Color::Blue, sf::Color::White);
    btns.push_back(btn);
    //btns.push_back(Button("hello", {150, 50}, 20, sf::Color::Blue, sf::Color::White));
    btns.at(i).setPosition({500, static_cast<float>(25 + 100 * i)});
    btns.at(i).setFont(arial);
  }


  int boxnum = 0;

  vector<Textbox> textboxes;
  float x_pos = 0, y_pos = 0;
  for (int i = 0; i < grid_size * grid_size; i++) {
    x_pos = 37 + ((i % grid_size) * box_size);
    y_pos = 25 + ((i / grid_size) * box_size);

    textboxes.push_back(Textbox(40, sf::Color::Blue));
    textboxes.at(i).setFont(arial);
    textboxes.at(i).setPosition({x_pos, y_pos});
    textboxes.at(i).setLimit(true,1);
    textboxes.at(i).setSelect(false);
  }

  bool sel;
  bool startTime = false;;
  int x = 0, y = 0;

  clock_t t;

  while(window.isOpen()) {

    sf::Vector2i position = sf::Mouse::getPosition(window);

    sf::Event event;
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed)
        window.close();

      if(event.type == sf::Event::MouseButtonPressed){
        switch(event.key.code) {
          case sf::Mouse::Left:
            sel = true;
            x = position.x;
            y = position.y;
        }

        for (int i = 0; i < 4; i++) {
          if (btns.at(i).isMouseOver(window)) {
            std::cout << "You clicked button " << i << std::endl;
          }

          if (btns.at(1).isMouseOver(window)) { // restart

            for (int i = 0; i < 81; i++)
              textboxes.at(i).empty();

            btns.at(3).setText("Start Time");
            startTime = false;
          }

          if (btns.at(3).isMouseOver(window)) {
            startTime = true;
          }
        }
      }

      if(event.type == sf::Event::TextEntered) {
        textboxes.at(boxnum).typedOn(event);

        try {
          int num = stoi(textboxes.at(boxnum).getText());
          grid.update_grid(num, boxnum % 9, boxnum / 9);
        } catch(const std::invalid_argument& ia) {
          // delete key???
          std::cerr << "Please enter an integer between 1 and 9, inclusive.\n";
          textboxes.at(boxnum).empty();
        }
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

    // drawing window
    if(sel){
      draw(true, x, y, boxnum);

      textboxes.at(boxnum).setSelect(true);
    } else {
      draw(false, 0, 0, boxnum);
    }

    for (int i = 0; i < 81; i++) {
      textboxes.at(i).drawTo(window);
    }

    for (int i = 0; i < 4; i++) {
      btns.at(i).drawTo(window);
    }

    if(startTime) {
      t = clock();
      // int sec = stoi(to_string(t)) / 1000;
      // int min = sec / 60;
      // sec = sec % 60;
      // printf("%2d:%2d\n", min, sec );

      // int sec = stoi(to_string(t)) / 1000;
      btns.at(3).setText("123 sec");
      //cout << t / 1000 << " seconds";
    }

    window.display();

  }
}


/* 
File input:
0 means not assigned value yet (user needs to input value)
integer between 1-9, inclusive, means that the num is fixed

get one char at a time
stoi to integer (error check) --> boxnum

draw that num onto grid

grid and box class?????

*/


