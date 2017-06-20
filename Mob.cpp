#include "Mob.h"
#include "PlayerController.h"

Mob::Mob()
{
}

Mob::Mob(const std::string fileName)
{
  loadTexture(fileName);
}

Mob::~Mob()
{
  delete pAttachedMobController_;
}

int Mob::loadTexture(const std::string fileName)
{
  if(!texture_.loadFromFile(fileName))
  {
    std::cout << "Load error!!!" << std::endl;
    return -1;
  }
  sprite_.setTexture(texture_);
  std::cout << "Load success!!!" << std::endl;
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
  position_ += sf::Vector2f(x, y);
}

void Mob::step(sf::Vector2f vector)
{
  position_ += vector;
}

void Mob::draw()
{
  Glb::game.drawSprite(sprite_);

}

sf::Vector2f Mob::getPosition()
{
  return position_;
}

void Mob::attachMobController(MobController* ptr)
{
  pAttachedMobController_ = ptr;
  pAttachedMobController_->setMob(*this);
}