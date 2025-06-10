#include "bulletColleague.h"
#include "bullet.h"

void BulletColleague::firedBullet()
{
    status->type = BULLET_FIRED;
    status->value = pBullet->getValue();
    mediator->notify(*status);
}