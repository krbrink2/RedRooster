#include "MobController.h"
#include "Mob.h"

MobController::MobController()
: mob_(NULL)
{
  ;
}

MobController::~MobController()
{

}

void MobController::setMob(Mob& mob)
{
  mob_ = &mob;
}