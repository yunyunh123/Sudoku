#pragma

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
  Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);
  void setText(std::string t);
  void setFont(sf::Font &font);
  void setBackColor(sf::Color color);
  void setTextColor(sf::Color color);
  void setPosition(sf::Vector2f pos);
  void drawTo(sf::RenderWindow &window);
  bool isMouseOver(sf::RenderWindow &window);

private:
  sf::RectangleShape button;
  sf::Text text;
  sf::Font font;
};