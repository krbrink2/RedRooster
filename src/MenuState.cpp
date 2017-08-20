#include "MenuState.h"

MenuState::MenuState()
  : activeButton_(0)
{}

MenuState::~MenuState()
{}

void MenuState::takeInput(sf::Event event)
{
  if(sf::Event::KeyPressed == event.type)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      activeButton_ = std::max(activeButton_ - 1, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      activeButton_ = std::min(activeButton_ + 1, static_cast<int>(buttons_.size() - 1));
    }
  }
  std::cout << activeButton_ << std::endl;
}

void MenuState::update()
{
  for(int i = 0; i < buttons_.size(); i++)
  {
    buttons_[i].update(i == activeButton_);
  }
}

void MenuState::draw()
{
 for(auto it = buttons_.begin(); it != buttons_.end(); it++)
  {
    it->draw();
  } 
}

