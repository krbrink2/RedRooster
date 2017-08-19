#include "Camera.h"
#include "Map.h"

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

void Camera::update()
{
  const float elasticity = .2;
  // If Camera is not very close to player mob, close part of the distance.
  sf::Vector2f playerPos = Gbl::pMap->pPlayerMob_->getPosition();
  sf::Vector2f cameraToPlayerVector = playerPos - getFocalPoint();
  if(abs(cameraToPlayerVector.x) + abs(cameraToPlayerVector.y) < 3)
  {
    // If very close, then leave the camera be.
    return;
  }
  setFocalPoint(getFocalPoint() + (cameraToPlayerVector * elasticity));
}