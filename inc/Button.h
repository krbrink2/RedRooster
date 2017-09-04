#ifndef BUTTON_H
#define BUTTON_H
#include "Globals.h"
#include "Drawable.h"


class Button
  : public Drawable
{
public:
  Button();
  ~Button();

  void update(bool active);
  void draw();

  std::string getString() const;
  sf::Vector2f getPosition() const;
  void setString(std::string string);
  void setPosition(double x, double y);
  void setPosition(sf::Vector2f pos);
  void setCallback(void (*callback)());

  void press();

//private:
  double         scale_;
  sf::Vector2f   position_;
  std::string    string_;
  sf::Text       text_;
  int            activeFrames_;
  // The action performed when pressed.
  void           (*callback_)();

};

#endif