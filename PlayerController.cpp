#include "PlayerController.h"
#include "Mob.h"

PlayerController::PlayerController()
: speed_(10)
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
    pMob_->step(0, -speed_);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    pMob_->step(-speed_, 0);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    pMob_->step(0, speed_);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    pMob_->step(speed_, 0);
  }
}