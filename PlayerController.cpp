#include "PlayerController.h"
#include "Mob.h"
#include <cmath>

PlayerController::PlayerController()
{

}

void PlayerController::takeInput(sf::Event event)
{
  eventQueue_.push(event);
}

bool PlayerController::eventQueueEmpty()
{
  return eventQueue_.empty();
}

void PlayerController::act()
{
  //@TODO finish as needed
  while(!eventQueueEmpty())
  {
    sf::Event event = eventQueue_.front();
    eventQueue_.pop();
    switch(event.type)
    {
      case sf::Event::KeyPressed:
        break;
      default:
        break;
    }
  }
  // Create velocity vector
  float x , y;
  x = y = 0;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    y += -1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    x += -1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    y += 1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    x += 1;
  }
  // Normalize vector
  float normalizer = std::sqrt((x*x) + (y*y));
  if(normalizer > 0)
  {
    normalizer = 1.0/normalizer;
  }
  else
  {
    normalizer = 0;
  }
  x *= normalizer*acceleration_;
  y *= normalizer*acceleration_;

  momentum_.x += x;
  momentum_.y += y;

  // Check for collision
  if(Gbl::pMap->checkForCollision(momentum_, *pMob_))
  {
    momentum_ = sf::Vector2f(0, 0);
  }

  pMob_->step(momentum_);
  momentum_ *= drag_;
}