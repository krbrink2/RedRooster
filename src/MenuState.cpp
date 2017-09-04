#include "MenuState.h"

MenuState::MenuState()
  : activeButton_(0)
{
  // Default to mainMenu
  setup(mainMenu);
}

MenuState::MenuState(menuType_t type)
  : activeButton_(0)
{
  setup(type);
}

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