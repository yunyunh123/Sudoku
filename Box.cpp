#include "Box.h"
#include <iostream>
#include <string>


Box::Box() {

}

Box::Box(int n, bool fixedVal) {
  num = n;
  fixed = fixedVal;
  correct = true;


  // sf::Font font;
  // if (!font.loadFromFile("arial.ttf")) {
  //   //Handle error
  // }

  // default font
  // if(!font.loadFromFile("arial.ttf")) {

  // }

  // Box has text if value is fixed
  // Box has  if value is not fixed (variable)

  if (fixed) {
    text.setCharacterSize(charSize);
    text.setString(to_string(num));
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
  } else {
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
  try {
    userText.typedOn(input);
    num = std::stoi(userText.getText());
  } catch (const std::invalid_argument& ia) {
    //what about delete key
    userText.empty();
   // std::cerr << "Please enter an integer between 1 and 9, inclusive.\n";

  }




}

void Box::clearAns() {
  userText.empty();
}