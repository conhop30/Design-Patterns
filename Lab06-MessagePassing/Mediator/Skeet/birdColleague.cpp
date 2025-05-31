#include "birdColleague.h"
#include "bird.h"

void BirdColleague::wentOutOfBounds()
{
    status->type = BIRD_DIED;
    status->value = -pBird->getPoints();
    mediator->notify(*status);
}

void BirdColleague::wasShot()
{
    status->type = BIRD_DIED;
    status->value = pBird->getPoints();
    mediator->notify(*status);
}