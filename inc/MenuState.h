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
  MenuState();
  // Declare but define anyways, thereby forcing MenuState to be pure abstract.
  virtual ~MenuState() = 0;

  virtual void takeInput(sf::Event event);
  virtual void update();
  virtual void draw();

//private 
  std::vector<Button> buttons_;
  int activeButton_;
};

#endif