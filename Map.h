#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Mob.h"
#include "Obstable.h"


class Map{
public:
	Map();
	Map(Map& rhs);
	Map& operator=(Map& rhs);
	~Map();

	void addMob(Mob& mob);

	vector<Mob*> mobPtrs;
	vector<Obstacle*> obstaclePtrs;
	

private:
	// Helper struct
	struct RegularGridBox{

	};


};





#endif
