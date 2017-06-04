#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/System.hpp>
#include "GameState.h"



class Game{
 public:
  Game();
  Game(Game& rhs);
  Game& operator=(Game& rhs);
  ~Game();

  /*void startClock();
  void pauseClock();
  void resetClock();*/

  void PushGameState(GameState* state);
  void PopGameState();

  sf::Clock clock;
 private:
  
  bool run;
  std::vector<GameState*> GameStateStack;
  
  
};



#endif
