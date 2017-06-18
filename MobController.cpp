#include "MobController.h"
#include "Mob.h"

MobController::MobController()
: pMob_(NULL)
{
  ;
}

MobController::~MobController()
{

}

void MobController::setMob(Mob& mob)
{
  pMob_ = &mob;
}