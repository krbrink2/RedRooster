#ifndef CAMERA_H
#define CAMERA_H
#include "Globals.h"

class Map;

class Camera : public Noncopyable
{
public:
  Camera();

  double        getViewScale() const;
  sf::Vector2f  getFocalPoint() const;
  void          setViewScale(double vs);
  void          setFocalPoint(sf::Vector2f fp);
  void          setPMap(Map* pMap);

//private:
  Map* pMap_;
  double viewScale_;
  sf::Vector2f focalPoint_;
};

#endif