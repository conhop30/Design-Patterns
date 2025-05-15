//
//  buoyancy.cpp
//  Lab03
//
//  Created by William Barr on 5/13/25.
//

#include "inertia.h"
#include "bird.h"
#include "buoyancy.h"


/*********************************************
 * FLOATER ADVANCE
 * How the floating bird moves: strong drag and anti-gravity
 *********************************************/
void Buoyancy::advance(Bird & bird)
{
   // small amount of drag
   bird.adjustVelocity(0.990);
   
   // inertia
   bird.adjustPosition(bird.getVelocity());
   
   // anti-gravity
   bird.addVelocityDy(0.05);
   
   // out of bounds checker
   if (bird.isOutOfBounds())
   {
      bird.kill();
      bird.adjustPoints(-1);; // points go negative when it is missed!
   }
}
