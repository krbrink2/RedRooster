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

  void press();

//private 
  void setup(menuType_t type);
  void setupMainMenu();
  void pressButton();
  void launchGame();

  std::vector<sf::Texture> textures_;
  std::vector<Button> buttons_;
  int activeButton_;
  GameState* pChildState_;
};

#endif