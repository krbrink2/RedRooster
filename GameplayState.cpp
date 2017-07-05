#include "GameplayState.h"
#include "PlayerController.h"

GameplayState::GameplayState()
: GameState()
, map_()
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

void GameplayState::draw()
{
    map_.draw();
}