#ifndef BUTTON_H
#define BUTTON_H
#include "Globals.h"
#include "Drawable.h"

class MenuState;

class Button
  : public Drawable
{
public:

  // The Syntax from the Black Lagoon
  // Pointer to a void-returning MenuState member function, with no arguments
  typedef void (MenuState::* CallbackToMenuState)();

  Button();
  ~Button();

  void update(bool active);
  void draw();

  std::string getString() const;
  sf::Vector2f getPosition() const;
  void setString(std::string string);
  void setPosition(double x, double y);
  void setPosition(sf::Vector2f pos);
  void setCallback(void (MenuState::*callback)());
  CallbackToMenuState getCallback();

//private:
  double         scale_;
  sf::Vector2f   position_;
  std::string    string_;
  sf::Text       text_;
  int            activeFrames_;
  // The action performed when pressed.
  CallbackToMenuState callback_;

};

#endif