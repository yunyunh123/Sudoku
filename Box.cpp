#include "Box.h"
#include <iostream>
#include <string>

Box::Box() {
}

Box::Box(int n, bool fixedVal) {
  num = n;
  fixed = fixedVal;
  correct = true;

  if (fixed) { // Creates a SFML text
    text.setCharacterSize(charSize);
    text.setString(to_string(num));
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
  } else { // Creates a textbox
    userText.setCharacterSize(charSize);
    userText.setFillColor(sf::Color::Blue);
    userText.setFont(font);
    userText.setLimit(true, 1);
    userText.setSelect(false);
  }
}

void Box::setFont(sf::Font &font) { 
  if(fixed) {
    text.setFont(font);
  } else {
    userText.setFont(font);
  }
}

void Box::fillAns(int n) {
  num = n;
  text.setString(to_string(num));
}

void Box::setPosition(sf::Vector2f pos) {
  if (fixed) {
    text.setPosition(pos);
  } else {
    userText.setPosition(pos);
  }
}

void Box::drawTo(sf::RenderWindow &window) {
  if (correct == false) {
    userText.setFillColor(sf::Color::Red);
  }

  if(fixed) {
    window.draw(text);
  } else {
    userText.drawTo(window);
  }
}

bool Box::isFixed() {
  return fixed;
}

void Box::select(bool sel) {
  if (not fixed) {
    userText.setSelect(sel);
  }
}

void Box::enterText(sf::Event input) {
  int temp;
  try {
    userText.typedOn(input);
    temp = std::stoi(userText.getText());

    // Ensure user does not type 0
    if (temp >= 1 and temp <= 9) {
      num = temp;
    } else {
      userText.empty();
    }
  } catch (const std::invalid_argument& ia) {
    userText.empty();
  }
}

void Box::clearAns() {
  userText.empty();
}