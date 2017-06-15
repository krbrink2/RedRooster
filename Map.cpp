#include "Map.h"
#include "PlayerController.h"

Map::Map()
//: pPlayerMob_(NULL)
{
  std::string icon = ICON;
  pPlayerMob_ = new Mob(icon);
  addMob(pPlayerMob_);
  pPlayerMob_->attachMobController(new PlayerController()); 
}

Map::~Map()
{
  clear();
}

void Map::addMob(Mob& mob)
{
  Mob* pMyMob  = new Mob();
  *pMyMob = mob;
  mobPtrs_.push_back(pMyMob);
}

void Map::addMob(Mob* pMob)
{
  mobPtrs_.push_back(pMob);
}

void Map::update()
{
  for(auto it = mobPtrs_.begin(); it != mobPtrs_.end(); it++)
  {
    (*it)->update();
  }
}

int Map::clear()
{
  for(auto it = mobPtrs_.begin(); it != mobPtrs_.end(); it++)
  {
    delete *it;
  }
  for(auto it = obstaclePtrs_.begin(); it != obstaclePtrs_.end(); it++)
  {
    delete *it;
  }
  return 0;
}