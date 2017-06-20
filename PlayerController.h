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


  double speed_ = 10; //@TODO unused
  double acceleration_ = 3;
  sf::Vector2f momentum_;
  float drag_ = .7;
  float maxMomentum_ = 30; //@TODO unused
  std::queue<sf::Event> eventQueue_;

};


#endif