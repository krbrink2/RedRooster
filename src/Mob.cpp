#include "Mob.h"
#include "Map.h"
#include "MobController.h"
#include "PlayerController.h"

Mob::Mob()
{
  boundingBox_.min_ = sf::Vector2f(position_.x, position_.y);
  boundingBox_.max_ = sf::Vector2f(position_.x + width_,
                                   position_.y + height_);
}

Mob::Mob(const std::string fileName)
{
  loadTexture(fileName);
  boundingBox_.min_ = sf::Vector2f(position_.x, position_.y);
  boundingBox_.max_ = sf::Vector2f(position_.x + width_,
                                   position_.y + height_);
}

Mob::~Mob()
{
  delete pAttachedMobController_;
}

void Mob::takeInput(sf::Event event)
{
  pAttachedMobController_->takeInput(event);
}

void Mob::update()
{
  pAttachedMobController_->act();
  sprite_.setPosition(position_);
}

void Mob::step(double x, double y)
{
  step(sf::Vector2f(x, y));
}

void Mob::step(sf::Vector2f vector)
{
  if(Gbl::pMap->checkForCollision(vector, *this))
  {
    std::cout << "Mob::step moving into another boundable! vector: " << vector.x << vector.y << std::endl;
    return;
  }
  position_ += vector;
  boundingBox_.min_ += vector;
  boundingBox_.max_ += vector;
}

void Mob::setPosition(double x, double y)
{
  setPosition(sf::Vector2f(x, y));
}

void Mob::setPosition(sf::Vector2f pos)
{
  position_ = pos;
  boundingBox_.min_ = pos;
  boundingBox_.max_ = pos + sf::Vector2f(width_, height_);
}
void Mob::setWidth(double w)
{
  width_ = w;
}

void Mob::setHeight(double h)
{
  height_ = h;
}

void Mob::draw()
{
  // @TODO: this needs to set sprite scale based on both Mob scale and Camera scale
  sf::Vector2f viewPosition = position_ - Gbl::pMap->camera_.getFocalPoint();
  viewPosition /= (float) Gbl::pMap->camera_.getViewScale();

  double viewScale = (float) scale_ / Gbl::pMap->camera_.getViewScale();

  sprite_.setPosition(viewPosition);
  sprite_.setScale(sf::Vector2f(viewScale, viewScale));
  Drawable::draw();
}

sf::Vector2f Mob::getPosition()
{
  return position_;
}

void Mob::attachMobController(MobController* ptr)
{
  if(NULL != pAttachedMobController_)
  {
    delete pAttachedMobController_;
  }
  pAttachedMobController_ = ptr;
  pAttachedMobController_->setMob(*this);
}
