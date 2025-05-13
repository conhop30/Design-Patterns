#include "inertia.h"
#include "bird.h"

void Inertia::advance(Bird & bird, int points)
{
    // small amount of drag
    bird.adjustVelocity() *= 0.995;

    // inertia
    bird.adjustPosition().add(bird.getVelocity());

    // out of bounds checker
    if (bird.isOutOfBounds())
    {
        bird.kill();
        points *= -1; // points go negative when it is missed!
    }
}