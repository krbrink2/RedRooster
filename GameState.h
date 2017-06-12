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
  GameState(StateType type);
  
  void takeInput(sf::Event event);

  StateType stateType_;

private:
  int init();


};

#endif
