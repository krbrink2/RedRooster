#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Globals.h"
#include "Mob.h"
#include "Obstable.h"


class Map{
public:
	Map();
	//Map(Map& rhs);
	//Map& operator=(Map& rhs);
	~Map();
	int clear();

	void addMob(Mob& mob);
	void addMob(Mob* pMob);

	vector<Mob*> mobPtrs_;
	vector<Obstacle*> obstaclePtrs_;

	Mob* pPlayerMob_;	// Does NOT live here.
	

private:
	// Helper struct
	struct RegularGridBox{

	};


};





#endif
