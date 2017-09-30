#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Globals.h"
#include "Drawable.h"

class Tile : public Drawable
{
public:
  Tile();

  //void draw();
  // Set this tile's place in the grid
  void setGridSpot(int x, int y);
  void getNinePoints(sf::Vector2f points[9]);

  bool visited_;


private:
  int gridX_, gridY_;
  sf::Vector2f coords_;

};

#endif