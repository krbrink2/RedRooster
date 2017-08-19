#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Camera.h"
#include "Globals.h"
#include "Mob.h"
#include "Noncopyable.h"
#include "Obstacle.h"

class PlayerController;

class Map : public Noncopyable
{
public:
	Map();
	~Map();
	int clear();

	void addDefaults();
	//void addMob(Mob& mob);
	void addMobPtr(Mob* pMob);
	void addObstacle(Obstacle* pObstacle);
	
	void update();
	void draw();

	bool checkForCollision(sf::Vector2f step, Boundable& b) const;

  Camera camera_;

//private:
	std::vector<Mob*> mobPtrs_;
	std::vector<Obstacle*> obstaclePtrs_;

	Mob* pPlayerMob_;	// Does NOT live here.
	PlayerController* pPlayerController_; // Does NOT live here
	

private:
	// Helper struct
	struct RegularGridBox{

	};


};





#endif
