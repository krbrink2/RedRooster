#include "GameplayState.h"

GameplayState::GameplayState()
: GameState()
{
  ;
}

void GameplayState::takeInput(sf::Event event)
{
  map_.pPlayerMob_->takeInput(event);
}