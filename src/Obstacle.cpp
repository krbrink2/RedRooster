#include "Obstacle.h"
#include "Map.h"

Obstacle::Obstacle()
{
  boundingBox_.min_ = sf::Vector2f(position_.x, position_.y);
  boundingBox_.max_ = sf::Vector2f(position_.x + width_,
                                   position_.y + height_);
}

Obstacle::Obstacle(const std::string fileName)
{
  loadTexture(fileName);
  boundingBox_.min_ = sf::Vector2f(position_.x, position_.y);
  boundingBox_.max_ = sf::Vector2f(position_.x + width_,
                                   position_.y + height_);
}

void Obstacle::draw()
{
  sf::Vector2f viewPosition = position_ - Gbl::pMap->camera_.getFocalPoint();
  viewPosition /= (float) Gbl::pMap->camera_.getViewScale();

  double viewScale = (float) scale_ / Gbl::pMap->camera_.getViewScale();

  sprite_.setPosition(viewPosition);
  sprite_.setScale(sf::Vector2f(viewScale, viewScale));
  Drawable::draw();
}

void Obstacle::setPosition(sf::Vector2f pos)
{
  position_ = pos;
  sprite_.setPosition(position_);
  boundingBox_.min_ = pos;
  boundingBox_.max_ = pos + sf::Vector2f(width_, height_);
  
}

void Obstacle::setPosition(float x, float y)
{
  setPosition(sf::Vector2f(x, y));
}