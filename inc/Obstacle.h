#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Globals.h"
#include "Boundable.h"


class Obstacle: public Boundable{
public:
  
	Obstacle();
  Obstacle(const std::string fileName);

  int loadTexture(const std::string fileName);
  void draw();
  void setPosition(float x, float y);
  void setPosition(sf::Vector2f pos);

  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::Vector2f position_ = sf::Vector2f(0, 0);
};



#endif
