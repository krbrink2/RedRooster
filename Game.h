#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"	

class Game{
 public:
  Game();
  Game(Game& rhs);
  Game& operator=(Game& rhs);
  ~Game();
  int clear();

  /*void startClock();
  void pauseClock();
  void resetClock();*/

  void pushGameState(GameState* state);
  void popGameState();
  void takeInput(sf::Event event);

  sf::Clock clock_;
  sf::RenderWindow window_;
  bool run_;
  std::vector<GameState*> gameStateStack_;
  
  
};



#endif
