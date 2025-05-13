//
//  gravity.cpp
//  Lab03
//
//  Created by William Barr on 5/13/25.
//

#include "inertia.h"
#include "bird.h"
#include "gravity.h"

/*********************************************
 * SINKER ADVANCE
 * How the sinker bird moves, no drag but gravity
 *********************************************/
void Gravity::advance(Bird & bird)
{
    // small amount of drag
    bird.addVelocityDy(-0.07);

    // inertia
    bird.adjustPosition(bird.getVelocity());

    // out of bounds checker
    if (bird.isOutOfBounds())
    {
        bird.kill();
       bird.adjustPoints(-1); // points go negative when it is missed!
    }
}
