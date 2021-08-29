#pragma

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Textbox.h"
#include<iostream>
#include <string>
#include<sstream>
using std::string;
using std::to_string;


class Box {
public:
  Box();
  Box(int n, bool fixedVal);
  void fillAns(int n);
  void setPosition(sf::Vector2f pos);
  void drawTo(sf::RenderWindow &window);
  void setFont(sf::Font &font);
  int num;// move back to private later
  bool isFixed();
  void select(bool sel);
  void enterText(sf::Event input);
  void clearAns();
  bool correct;
private:
  const int charSize = 40; // i should have a separate function for this
  sf::Font font;
  sf::Text text;
  Textbox userText;
  int row; // should this be public or private?
  int col;
  bool fixed; // given value or not?

  //sf::Font font;

};

