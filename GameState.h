#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class GameState{
public:

  GameState();
  virtual ~GameState();
  
  virtual void takeInput(sf::Event event) = 0;

};

#endif
