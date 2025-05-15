//
//  chaos.cpp
//  Lab03
//
//  Created by William Barr on 5/13/25.
//

#include "inertia.h"
#include "bird.h"
#include "chaos.h"
#include <cassert>

/******************************************************************
 * RANDOM
 * These functions generate a random number.
 ****************************************************************/
int randomIntCrazy(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double randomFloatCrazy(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}

/*********************************************
 * CRAZY ADVANCE
 * How the crazy bird moves, every half a second it changes direciton
 *********************************************/
void Chaos::advance(Bird & bird)
{
   // erratic turns eery half a second or so
   if (randomIntCrazy(0, 15) == 0)
   {
      bird.addVelocityDy(randomFloatCrazy(-1.5, 1.5));
      bird.addVelocityDx(randomFloatCrazy(-1.5, 1.5));
   }
   
   // inertia
   bird.adjustPosition(bird.getVelocity());
   
   // out of bounds checker
   if (bird.isOutOfBounds())
   {
      bird.kill();
      bird.adjustPoints(-1); // points go negative when it is missed!
   }
}
