#ifndef MOBCONTROLLER_H
#define MOBCONTROLLER_H

class Mob;

class MobController{
public:
	MobController();

	void setMob(Mob& mob);

	Mob* mob_;
};

#endif
