#include "GameplayState.h"
#include "PlayerController.h"

GameplayState::GameplayState()
: GameState()
{
}

GameplayState::~GameplayState()
{
  map_.clear();
}

void GameplayState::takeInput(sf::Event event)
{
  map_.pPlayerMob_->takeInput(event);
}

void GameplayState::update()
{
  map_.update();
}