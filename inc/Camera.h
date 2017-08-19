#ifndef CAMERA_H
#define CAMERA_H
#include "Globals.h"
#include "Map.h"


class Camera : public Noncopyable
{
public:
  Camera();

  double        getViewScale();
  sf::Vector2f   getFocalPoint();
  void          setViewScale(double vs);
  void          setFocalPoint(sf::Vector2f fp);


  double viewScale;
  sf::Vector2f focalPoint;
};

#endif