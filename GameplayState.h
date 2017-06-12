#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H
#include "Globals.h"
#include "GameState.h"

class GameplayState: public GameplayState
{
public:
  GameplayState();

  void takeInput(sf::Event event) = 0;

};



#endif