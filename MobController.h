#ifndef MOBCONTROLLER_H
#define MOBCONTROLLER_H
#include "Globals.h"
#include "Map.h"

class Mob;

class MobController{
public:
	MobController();
  virtual ~MobController();

	void setMob(Mob& mob);
  virtual void takeInput(sf::Event event) = 0;
  virtual void act() = 0;

	Mob* pMob_; // Does NOT live here.
};

#endif
