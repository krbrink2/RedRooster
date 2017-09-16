#include "MenuState.h"
#include "GameplayState.h"

MenuState::MenuState()
  : activeButton_(0)
  , pChildState_(NULL)
{
  // Default to mainMenu
  setup(mainMenu);
}

MenuState::MenuState(menuType_t type)
  : activeButton_(0)
  , pChildState_(NULL)
{
  setup(type);
}

MenuState::~MenuState()
{
  if(pChildState_)
  {
    delete pChildState_;
    pChildState_ = NULL;
  }
}

void MenuState::takeInput(sf::Event event)
{
  if(pChildState_)
  {
    pChildState_->takeInput(event);
    return;
  }

  if(sf::Event::KeyPressed == event.type)
  {
    // Up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      activeButton_ = std::max(activeButton_ - 1, 0);
    }
    // Down 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      activeButton_ = std::min(activeButton_ + 1, static_cast<int>(buttons_.size() - 1));
    }
    // Enter key
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
      Button::CallbackToMenuState callback = buttons_[activeButton_].getCallback();
      if(callback) // Null check
      {
        (this->*callback)();
      }
    }
  }
  std::cout << activeButton_ << std::endl;
}

void MenuState::update()
{
  if(pChildState_)
  {
    pChildState_->update();
    return;
  }

  for(int i = 0; i < buttons_.size(); i++)
  {
    buttons_[i].update(i == activeButton_);
  }
}

void MenuState::draw()
{
  if(pChildState_)
  {
    pChildState_->draw();
    return;
  }

 for(auto it = buttons_.begin(); it != buttons_.end(); it++)
  {
    it->draw();
  } 
}

void MenuState::setup(menuType_t type)
{
  switch(type)
  {
    case mainMenu:
      setupMainMenu();
      break;
    default:
      setupMainMenu();
      break;
  }
}

void MenuState::setupMainMenu()
{
  // Load main menu textures
  textures_.push_back(sf::Texture());
  textures_.back().loadFromFile(BUTTON);

  // Add main menu buttons
  int midscreen    = Gbl::game.gameWindowWidth_ * .5;
  int windowHeight = Gbl::game.gameWindowHeight_;
  // Add start button
  buttons_.push_back(Button());
  buttons_.back().setTexture(textures_.back());
  buttons_.back().setPosition(sf::Vector2f(midscreen, windowHeight*.25));
  buttons_.back().setString(std::string("Start!"));
  buttons_.back().setCallback(&MenuState::launchGame);

  // Add options button
  buttons_.push_back(Button());
  buttons_.back().setTexture(textures_.back());
  buttons_.back().setPosition(sf::Vector2f(midscreen, windowHeight*.5));
  buttons_.back().setString(std::string("Options"));

  // Add quit button
  buttons_.push_back(Button());
  buttons_.back().setTexture(textures_.back());
  buttons_.back().setPosition(sf::Vector2f(midscreen, windowHeight*.75));
  buttons_.back().setString(std::string("Quit"));
}

void MenuState::launchGame()
{
  pChildState_ = new GameplayState();
}

