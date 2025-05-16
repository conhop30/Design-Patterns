/***********************************************************************
 * Header File:
 *    Apply Movement : How birds can move across the screen
 * Author:
 *    Cougar Taylor
 * Summary:
 *    All the ways the birds can move across the screen
 ************************************************************************/

#pragma once
#include <cassert>
#include "position.h"

// Forward declarations for random functions
int randomInt(int min, int max);
double randomFloat(double min, double max);

/**********************
 * ApplyMovement
 * How birds can move across the screen
 **********************/
class ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) = 0;
   virtual ~ApplyMovement() {}
};

class ApplyInertia : public ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) override
   {
      pt.add(v);
   }
};

class ApplyDrag : public ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) override
   {
      v *= 0.990;
   }
};

class ApplyAntiGravity : public ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) override
   {
      v.addDy(0.05);
   }
};

class ApplyGravity : public ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) override
   {
      v.addDy(-0.07);
   }
};

class ApplyTurn : public ApplyMovement
{
public:
   virtual void AffectMovement(Position& pt, Velocity& v) override
   {
      if (randomInt(0, 15) == 0)
      {
         v.addDy(randomFloat(-1.5, 1.5));
         v.addDx(randomFloat(-1.5, 1.5));
      }
   }
};