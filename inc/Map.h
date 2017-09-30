#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Camera.h"
#include "Globals.h"
#include "Mob.h"
#include "Noncopyable.h"
#include "Obstacle.h"
#include "Tile.h"
#include "Ray.h"

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
	void createTiles();
	void castRay(Ray& ray);

  Camera camera_;

	std::vector<Mob*> mobPtrs_;
	std::vector<Obstacle*> obstaclePtrs_;
	std::vector< std::vector<Tile> > tiles_;

	Mob* pPlayerMob_;	// Does NOT live here.
	unsigned gridWidth_  = 10;
	unsigned gridHeight_ = 10;

//private:
	PlayerController* pPlayerController_; // Does NOT live here
	int tileSize_;
	

private:
	// Helper struct
	struct RegularGridBox{

	};

};





#endif
