#include "Camera.h"

Camera::Camera()
{
}

double Camera::getViewScale() const
{
  return viewScale_;
}

sf::Vector2f Camera::getFocalPoint() const
{
  return focalPoint_;
}

void Camera::setViewScale(double vs)
{
  viewScale_ = vs;
}

void Camera::setFocalPoint(sf::Vector2f fp)
{
  focalPoint_ = fp;
}

void Camera::setPMap(Map* pMap)
{
  pMap_ = pMap;
}