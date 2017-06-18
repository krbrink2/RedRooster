#include "PlayerController.h"

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
  //@TODO
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
}