#include "Ray.h"

Ray::Ray()
  : origin_(sf::Vector2f(0,0))
  , dir_(sf::Vector2f(0,0))
  , dest_(sf::Vector2f(0,0))
{
}

Ray::Ray(sf::Vector2f origin, sf::Vector2f dir)
  : origin_(origin)
  , dir_(dir)
  , dest_(sf::Vector2f(0,0))
{
}

void Ray::setOrigin(sf::Vector2f origin)
{
  origin_ = origin;
}

void Ray::setDir(sf::Vector2f dir)
{
  dir_ = dir;
}

void Ray::setDest(sf::Vector2f dest)
{
  dest_ = dest;
}