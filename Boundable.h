#ifndef BOUNDABLE_H
#define BOUNDABLE_H
#include "Globals.h"


class Boundable
{
public:
  struct BoundingBox
  {
    sf::Vector2f min_ = sf::Vector2f(-.5, -.5);
    sf::Vector2f max_ = sf::Vector2f(.5, .5);
    
  };

  bool checkForIntersection(const Boundable& other) const;
  bool checkForIntersection(const sf::Vector2f step, const Boundable& other) const;

  BoundingBox boundingBox_;

};

#endif
