#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H
#include "Globals.h"
#include "GameState.h"
#include "Map.h"
#include "Mob.h"

class GameplayState: public GameState
{
public:
  GameplayState();
  ~GameplayState();

  void takeInput(sf::Event event);

  Map map_;


};



#endif