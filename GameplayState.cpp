#include "GameplayState.h"

GameplayState::GameplayState
: GameState()
{

}

GameplayState::~GameState()
{
  clear();
}

int GameplayState::clear()
{
  map_.clear();
}

void GameplayState::takeInput(sf::Event event)
{
  map_.pPlayerMob_.takeInput(event);
}