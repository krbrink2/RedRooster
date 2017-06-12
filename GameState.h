#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class GameState{
public:

  enum StateType{
    MAIN_MENU,
    OPTIONS_MENU,
    GAMEPLAY,
    POPUP_MENU
  };


  GameState();
  virtual int clear() = 0;
  
  virtual void takeInput(sf::Event event) = 0;

  StateType stateType_;

private:
  //virtual int init() = 0;


};

#endif
