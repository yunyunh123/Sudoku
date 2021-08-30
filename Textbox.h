#pragma
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <sstream>

using std::string;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
  // Constructor
  Textbox();
  Textbox(int size, sf::Color color);

  // Public methods
  void setCharacterSize(int size);
  void setFillColor(sf::Color color);
  void setFont(sf::Font &font);
  void setPosition(sf::Vector2f pos);
  void setLimit(bool ToF, int lim);
  bool selected();
  void setSelect(bool sel);
  std::string getText();
  void empty();
  void drawTo(sf::RenderWindow &window);
  void typedOn(sf::Event input);

private:
  // Private attributes
  sf::Text textbox;
  std::ostringstream text;
  bool isSelected = false;
  bool hasLimit = false;
  int limit;

  // Private methods
  void inputLogic(int charTyped);
  void deleteLastChar();
};