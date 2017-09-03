#include "Button.h"
#include "Map.h"

Button::Button()
  : scale_(.1)
  , position_(sf::Vector2f(0, 0))
  , string_("Hello, world!")
  , activeFrames_(0)
{
  text_.setFont(Gbl::game.font_);
  text_.setCharacterSize(24);
  //text_.setFillColor(sf::Color::Black);
}

Button::~Button()
{}

void Button::update(bool active)
{
  // Make sure the sprite's origin is set. 
  // This is a poor place to do this, but otherwise
  // I'd have to overload several Drawable methods.
  //
  sprite_.setOrigin(sf::Vector2f(sprite_.getTexture()->getSize()) * .5f);

  if(active)
  {
    activeFrames_ = 0;
    scale_ = .15;
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
  Gbl::game.window_.draw(text_);
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
  text_.setString(string_);
}

void Button::setPosition(double x, double y)
{
  setPosition(sf::Vector2f(x, y));
}

void Button::setPosition(sf::Vector2f pos)
{
  position_ = pos;
}