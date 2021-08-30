// Copyright 2021 Julia Hua jhua2@bu.edu

#pragma

#include "Textbox.h"
#include<iostream>
#include <string>
#include<sstream>
using std::string;
using std::to_string;
// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>

class Box {
public:
  // Constructors
  Box();
  Box(int n, bool fixedVal);

  // Public functions
  void fillAns(int n);
  void setPosition(sf::Vector2f pos);
  void drawTo(sf::RenderWindow &window);
  void setFont(sf::Font &font);
  bool isFixed();
  void select(bool sel);
  void enterText(sf::Event input);
  void clearAns();

  // Public attributes
  bool correct;
  int num;

private:
  // Private attributes
  const int charSize = 40;
  sf::Font font;
  sf::Text text;
  Textbox userText;
  int row;
  int col;
  bool fixed;
};

