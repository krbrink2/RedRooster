#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Globals.h"
#include "Boundable.h"
#include "Drawable.h"


class Obstacle
  : public Boundable
  , public Drawable
{
public:
  
	Obstacle();
  Obstacle(const std::string fileName);

  void draw();
  void setPosition(float x, float y);
  void setPosition(sf::Vector2f pos);

  double scale_          = 1;
  sf::Vector2f position_ = sf::Vector2f(0, 0);
  double width_          = 100;
  double height_         = 100;
};



#endif
