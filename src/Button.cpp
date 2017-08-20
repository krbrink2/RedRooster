#include "Button.h"
#include "Map.h"

Button::Button()
  : scale_(.1)
  , position_(sf::Vector2f(0, 0))
  , string_("Hello, world!")
  , activeFrames_(0)
{}

Button::~Button()
{}

void Button::update(bool active)
{
  if(active)
  {
    activeFrames_ = 0;
    scale_ = .2;
  }
  else
  {
    activeFrames_++;
    scale_ = .1;
  }
}

void Button::draw()
{
  sprite_.setPosition(position_);
  // @TODO move the sprite's position to account for scale
  sprite_.setScale(sf::Vector2f(scale_, scale_));
  Drawable::draw();
}

std::string Button::getString() const
{
  return string_;
}

sf::Vector2f Button::getPosition() const
{
  return position_;
}

void Button::setString(std::string string)
{
  string_ = string;
}

void Button::setPosition(double x, double y)
{
  setPosition(sf::Vector2f(x, y));
}

void Button::setPosition(sf::Vector2f pos)
{
  position_ = pos;
}