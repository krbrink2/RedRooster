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
  void update();
  void draw();

  Map map_;


};



#endif