#include "GameState.h"

GameState::GameState()
  :stateType_(StateType::GAMEPPLAY)
{
  init();
};

GameState::GameState(StateType type)
  :stateType_(type)
{
  init();
};

int GameState::init()
{
  
};