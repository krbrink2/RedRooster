#include "PlayerController.h"
#include "Mob.h"

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
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    momentum_.y -= acceleration_;
    momentum_.y = std::max(momentum_.y, -maxMomentum_);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    momentum_.x -= acceleration_;
    momentum_.x = std::max(momentum_.x, -maxMomentum_);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    momentum_.y += acceleration_;
    momentum_.y = std::min(momentum_.y, maxMomentum_);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    momentum_.x += acceleration_;
    momentum_.x = std::min(momentum_.x, maxMomentum_);
  }
  pMob_->step(momentum_);
  momentum_ *= drag_;
}