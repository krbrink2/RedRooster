#ifndef RAY_H
#define RAY_H
#include "Globals.h"

class Ray
{
  Ray();
  Ray(sf::Vector2f origin, sf::Vector2f dir);

  sf::Vector2f getOrigin();
  sf::Vector2f getDir();
  sf::Vector2f getDest();

  void setOrigin(sf::Vector2f origin);
  void setDir(sf::Vector2f dir);
  void setDest(sf::Vector2f dest);

  void normalize();

private:
  sf::Vector2f origin_;
  sf::Vector2f dir_;
  sf::Vector2f dest_;
};

#endif