#include "birdColleague.h"
#include "bird.h"

void BirdColleague::wentOutOfBounds()
{
    message->type = BIRD_DIED;
    message->value = -pBird->getPoints();
    mediator->notify(*message);
}

void BirdColleague::wasShot()
{
    message->type = BIRD_DIED;
    message->value = pBird->getPoints();
    mediator->notify(*message);
}