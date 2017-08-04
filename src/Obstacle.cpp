#include "Obstacle.h"

Obstacle::Obstacle()
{
  boundingBox_.min_ = sf::Vector2f(-100, -100);
  boundingBox_.max_ = sf::Vector2f(100, 100);
}

Obstacle::Obstacle(const std::string fileName)
{
  loadTexture(fileName);
  boundingBox_.min_ = sf::Vector2f(-100, -100);
  boundingBox_.max_ = sf::Vector2f(100, 100);
}

void Obstacle::draw()
{
  Gbl::game.drawSprite(sprite_);
}

int Obstacle::loadTexture(const std::string fileName)
{
  if(!texture_.loadFromFile(fileName))
  {
    std::cout << "Load error in " << __PRETTY_FUNCTION__ << std::endl;
    return -1;
  }
  sprite_.setTexture(texture_);
  return 0;
}

void Obstacle::setPosition(sf::Vector2f pos)
{
  position_ = pos;
  sprite_.setPosition(position_);
  
}

void Obstacle::setPosition(float x, float y)
{
  setPosition(sf::Vector2f(x, y));
}