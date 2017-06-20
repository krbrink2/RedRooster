#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <queue>
#include "Globals.h"
#include "MobController.h"


class PlayerController: public MobController
{
public:
	PlayerController();

	void takeInput(sf::Event event);
  void act();
  bool eventQueueEmpty();


  double speed_;
  std::queue<sf::Event> eventQueue_;

};


#endif