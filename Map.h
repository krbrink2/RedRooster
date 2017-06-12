#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Globals.h"
#include "Mob.h"
#include "Obstacle.h"


class Map{
public:
	Map();
	//Map(Map& rhs);
	//Map& operator=(Map& rhs);
	~Map();
	int clear();

	void addMob(Mob& mob);
	void addMob(Mob* pMob);

	std::vector<Mob*> mobPtrs_;
	std::vector<Obstacle*> obstaclePtrs_;

	Mob* pPlayerMob_;	// Does NOT live here.
	

private:
	// Helper struct
	struct RegularGridBox{

	};


};





#endif
