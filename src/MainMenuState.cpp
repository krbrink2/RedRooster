#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
  // Add main menu buttons!
  // Add start button
  buttons_.push_back(Button());
  buttons_.back().loadTexture(BUTTON);
  buttons_.back().setPosition(sf::Vector2f(400, 0));
  buttons_.back().setString(std::string("Start!"));

  // Add options button
  buttons_.push_back(Button());
  buttons_.back().loadTexture(BUTTON);
  buttons_.back().setPosition(sf::Vector2f(400, 200));
  buttons_.back().setString(std::string("Options"));

  // Add quit button
  buttons_.push_back(Button());
  buttons_.back().loadTexture(BUTTON);
  buttons_.back().setPosition(sf::Vector2f(400, 400));
  buttons_.back().setString(std::string("Quit"));
}

MainMenuState::~MainMenuState()
{}