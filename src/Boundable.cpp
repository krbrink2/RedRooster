#include "Boundable.h"
#include "Globals.h"

bool Boundable::checkForIntersection(const Boundable& other) const
{
  if(this == &other)
  {
    return false;
  }
  // (RectA.Left < RectB.Right && RectA.Right > RectB.Left &&
  //    RectA.Top > RectB.Bottom && RectA.Bottom < RectB.Top ) 
  return boundingBox_.min_.x < other.boundingBox_.max_.x 
          && boundingBox_.max_.x > other.boundingBox_.min_.x
          && boundingBox_.max_.y > other.boundingBox_.min_.y
          && boundingBox_.min_.y < other.boundingBox_.max_.y;
}

bool Boundable::checkForIntersection(const sf::Vector2f step, const Boundable& other) const
{
  if(this == &other)
  {
    return false;
  }
  sf::Vector2f myMin = boundingBox_.min_ + step;
  sf::Vector2f myMax = boundingBox_.max_ + step;
  return myMin.x < other.boundingBox_.max_.x 
          && myMax.x > other.boundingBox_.min_.x
          && myMax.y > other.boundingBox_.min_.y
          && myMin.y < other.boundingBox_.max_.y;
}
