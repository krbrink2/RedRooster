#include "Mob.h"
#include "PlayerController.h"

Mob::Mob()
: scale_(1)
, x_(0)
, y_(0)
, shape_(100.f)
{
  shape_.setFillColor(sf::Color::Green);
}

Mob::Mob(const std::string fileName)
: texture_()
, sprite_()
, scale_(1)
, x_(0)
, y_(0)
, shape_(100.f)
{
  loadTexture(fileName);
  shape_.setFillColor(sf::Color::Green);
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
  sprite_.setPosition(sf::Vector2f(x_, y_));
}

void Mob::step(double x, double y)
{
  x_ += x;
  y_ += y;
}

void Mob::draw()
{
  Glb::game.drawSprite(shape_);
  Glb::game.drawSprite(sprite_);

}


Mob::~Mob()
{
  delete pAttachedMobController_;
}

void Mob::attachMobController(MobController* ptr)
{
  pAttachedMobController_ = ptr;
}