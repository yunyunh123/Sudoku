#include "Button.h"

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
  // default font:
  if(!font.loadFromFile("arial.ttf")) {
  }
  
  text.setFont(font);
  text.setString(t);
  text.setFillColor(textColor);
  text.setCharacterSize(charSize);

  button.setSize(size);
  button.setFillColor(bgColor);
}

void Button::setText(std::string t) {
  text.setString(t);
}

void Button::setFont(sf::Font &font) {
  text.setFont(font);
}

void Button::setBackColor(sf::Color color) {
  button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
  text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
  button.setPosition(pos);

  float xPos = (pos.x + button.getLocalBounds().width / 2) - text.getLocalBounds().width / 2;
  float yPos = (pos.y + button.getLocalBounds().height / 2) - text.getLocalBounds().height / 2;
  text.setPosition({xPos, yPos});
}

void Button::drawTo(sf::RenderWindow &window) {
  window.draw(button);
  window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float btnPosX = button.getPosition().x;
  float btnPosY = button.getPosition().y;

  float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
  float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

  if (mouseX < btnxPosWidth and mouseX > btnPosX and mouseY < btnyPosHeight and mouseY > btnPosY) {
    return true;
  }
  return false;
}