#include "Map.h"
#include "PlayerController.h"

Map::Map()
//: pPlayerMob_(NULL)
{
  std::string icon = ICON;
  pPlayerMob_ = new Mob(icon);

  pPlayerController* PlayerController();
  pPlayerController->pMap = this;
  pPlayerMob_->attachMobController(PlayerController); 
  addMobPtr(pPlayerMob_);
  addDefaults();
}

Map::~Map()
{
  clear();
}

void Map::addDefaults()
{
  Obstacle* pObstacle;
  pObstacle = new Obstacle(OBSTACLE);
  pObstacle->setPosition(10, 10);
  addObstacle(pObstacle);
  pObstacle = new Obstacle(OBSTACLE);
  pObstacle->setPosition(350, 200);
  addObstacle(pObstacle);
}

// void Map::addMob(Mob& mob)
// {
//   Mob* pMyMob  = new Mob();
//   *pMyMob = mob;
//   mobPtrs_.push_back(pMyMob);
// }

void Map::addMobPtr(Mob* pMob)
{
  pMob->pMap_ = this;
  if(NULL == pMob->pAttachedMobController_)
  {
    //@TODO add some default controller. //@RESUME
  }
  mobPtrs_.push_back(pMob);
}

void Map::addObstacle(Obstacle* pObstacle)
{
  obstaclePtrs_.push_back(pObstacle);
}

void Map::update()
{
  for(auto it = mobPtrs_.begin(); it != mobPtrs_.end(); it++)
  {
    (*it)->update();
  }
}

void Map::draw()
{
  for(auto it = mobPtrs_.begin(); it != mobPtrs_.end(); it++)
  {
    (*it)->draw();
  }
  for(auto it = obstaclePtrs_.begin(); it != obstaclePtrs_.end(); it++)
  {
    (*it)->draw();
  }
}

int Map::clear()
{
  for(auto it = mobPtrs_.begin(); it != mobPtrs_.end(); it++)
  {
    delete *it;
  }
  mobPtrs_.clear();
  for(auto it = obstaclePtrs_.begin(); it != obstaclePtrs_.end(); it++)
  {
    delete *it;
  }
  obstaclePtrs_.clear();
  pPlayerMob_ = NULL;
  return 0;
}