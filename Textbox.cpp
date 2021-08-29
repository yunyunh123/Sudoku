#include "Textbox.h"

Textbox::Textbox() {

}

Textbox::Textbox(int size, sf::Color color) {
  textbox.setCharacterSize(size);
  textbox.setFillColor(color);
}

void Textbox::setCharacterSize(int size) {
  textbox.setCharacterSize(size);
}

void Textbox::setFillColor(sf::Color color) {
  textbox.setFillColor(color);
}

void Textbox::setFont(sf::Font &font) { 
  textbox.setFont(font); 
}

void Textbox::setPosition(sf::Vector2f pos) {
  textbox.setPosition(pos);
}

void Textbox::setLimit(bool ToF, int lim) {
  hasLimit = ToF;
  limit = lim - 1;
}

bool Textbox::selected() {
  return isSelected;
}
void Textbox::setSelect(bool sel) {
  isSelected = sel;
}

std::string Textbox::getText() {
  return text.str();
}

void Textbox::drawTo(sf::RenderWindow &window) {
  window.draw(textbox);
}

void Textbox::typedOn(sf::Event input) {
  if(isSelected) {
    int charTyped = input.text.unicode;
    if (charTyped < 128) {

      if (hasLimit) {
        if (text.str().length() <= limit) {
          inputLogic(charTyped);
        } else if (text.str().length() > limit and charTyped == DELETE_KEY) {
          deleteLastChar();
        }
      } 

      else {
        inputLogic(charTyped);
      } 

    }
  }
}

void Textbox::empty() {
  text.str("");
  textbox.setString(text.str());
}

void Textbox::inputLogic(int charTyped) {
  if (charTyped != DELETE_KEY) {
    text << static_cast<char>(charTyped);
  }
  else if (charTyped == DELETE_KEY)
  {
    if (text.str().length() > 0) {  // char exists to be deleted
      deleteLastChar();
    }
  }

  textbox.setString(text.str());
}

void Textbox::deleteLastChar() {
  std::string t = text.str();
  std::string newT = "";

  for (int i = 0; i < t.length() - 1; i++) {
    newT += t.at(i); // copies each value except the last char
  }
  text.str(""); 
  text << newT;

  textbox.setString(text.str());
}