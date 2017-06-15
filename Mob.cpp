#include "Mob.h"
#include "PlayerController.h"

Mob::Mob()
: scale_(1)
, x_(0)
, y_(0)
{
  ;
}

Mob::Mob(const std::string fileName)
: scale_(1)
, x_(0)
, y_(0)
{
  loadTexture(fileName);
}

int Mob::loadTexture(const std::string fileName)
{
  if(!texture_.loadFromFile(fileName))
  {
    return -1;
  }
  return 0;
}

void Mob::takeInput(sf::Event event)
{
  pAttachedMobController_->takeInput(event);
}

void Mob::update()
{
  pAttachedMobController_->act();
}


Mob::~Mob()
{
  delete pAttachedMobController_;
}

void Mob::attachMobController(MobController* ptr)
{
  pAttachedMobController_ = ptr;
}