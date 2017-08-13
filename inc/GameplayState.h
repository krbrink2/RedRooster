#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H
#include "Globals.h"
#include "GameState.h"
#include "Map.h"
#include "Mob.h"

class GameplayState : public GameState
                    , public Noncopyable
{
public:
  GameplayState();
  ~GameplayState();

  void takeInput(sf::Event event);
  void update();
  void draw();

private:
  Map map_;


};



#endif