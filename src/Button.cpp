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
  sprite_.setOrigin(sf::Vector2f(sprite_.getTexture()->getSize()) * .5f);
  sprite_.setScale(sf::Vector2f(scale_, scale_));
  Drawable::draw();


  text_.setPosition(position_);
  sf::FloatRect textBounds = text_.getLocalBounds();
  text_.setOrigin(sf::Vector2f(textBounds.width*.5, textBounds.height*.5));
  text_.setScale(sf::Vector2f(scale_*10, scale_*10));
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