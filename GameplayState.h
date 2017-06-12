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
  int clear();

  void takeInput(sf::Event event) = 0;

  Map map_;


};



#endif