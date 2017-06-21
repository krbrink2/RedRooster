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
        std::cout << "Key pressed!" << std::endl;
        break;
      default:
        //std::cout << "Other event!" << std::endl;
        break;
    }
  }
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

  pMob_->step(momentum_);
  momentum_ *= drag_;
}