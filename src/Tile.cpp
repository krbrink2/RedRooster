#include "Tile.h"

Tile::Tile()
  : gridX_(0)
  , gridY_(0)
  , coords_(sf::Vector2f(0,0))
{
}

void Tile::setGridSpot(int x, int y)
{
  gridX_ = x;
  gridY_ = y;
}

void Tile::getNinePoints(sf::Vector2f points[9])
{
  //@TODO
}