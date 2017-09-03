#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "Globals.h"
#include "GameState.h"
#include "Button.h"


class MenuState
  : public GameState
  , public Noncopyable
{
public:

  enum menuType_t
  {
    mainMenu
  };

  MenuState();
  MenuState(menuType_t type);
  ~MenuState();

  void takeInput(sf::Event event);
  void update();
  void draw();

//private 
  void setup(menuType_t type);
  void setupMainMenu();

  std::vector<Button> buttons_;
  int activeButton_;
};

#endif