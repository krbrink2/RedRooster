#include "Mob.h"
#include "MobController.h"
#include "PlayerController.h"

Mob::Mob()
{
  boundingBox_.min_ = sf::Vector2f(-100, -100);
  boundingBox_.max_ = sf::Vector2f(100, 100);
}

Mob::Mob(const std::string fileName)
{
  loadTexture(fileName);
  boundingBox_.min_ = sf::Vector2f(-100, -100);
  boundingBox_.max_ = sf::Vector2f(100, 100);
}

Mob::~Mob()
{
  delete pAttachedMobController_;
}

int Mob::loadTexture(const std::string fileName)
{
  if(!texture_.loadFromFile(fileName))
  {
    std::cout << "Load error in " << __PRETTY_FUNCTION__ << std::endl;
    return -1;
  }
  sprite_.setTexture(texture_);
  return 0;
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
  // Check for collision  
  //@RESUME
  position_ += vector;
}

void Mob::setPosition(double x, double y)
{
  setPosition(sf::Vector2f(x, y));
}

void Mob::setPosition(sf::Vector2f pos)
{
  position_ = pos;
}

void Mob::draw()
{
  Gbl::game.drawSprite(sprite_);
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
