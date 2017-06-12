#ifndef MOBCONTROLLER_H
#define MOBCONTROLLER_H
#include "Mob.h"

class MobController{
public:
	MobController();

	void setMob(Mob& mob);

	Mob* mob_;
};

#endif
