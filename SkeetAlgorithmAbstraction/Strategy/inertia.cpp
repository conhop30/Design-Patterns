#include "inertia.h"
#include "bird.h"

/*********************************************
 * STANDARD ADVANCE
 * How the standard bird moves - inertia and drag
 *********************************************/
void Inertia::advance(Bird & bird)
{
    // small amount of drag
    bird.adjustVelocity(0.995);

    // inertia
    bird.adjustPosition(bird.getVelocity());

    // out of bounds checker
    if (bird.isOutOfBounds())
    {
        bird.kill();
       bird.adjustPoints(-1); // points go negative when it is missed!
    }
}
