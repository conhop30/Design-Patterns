/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
#include <list>
#include <cassert>



/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet
{
protected:
   static Position dimensions;   // size of the screen
   Position pt;                  // position of the bullet
   Velocity v;                   // velocity of the bullet
   double radius;                // the size (radius) of the bullet
   bool dead;                    // is this bullet dead?
   int value;                    // how many points does this cost?
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // setters
   void kill()                   { dead = true; }
   void setValue(int newValue)   { value = newValue; }
   
   // getters
   bool isDead()           const { return dead;   }
   Position getPosition()  const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getValue()          const { return value;  }

   // special functions
   virtual void death(std::list<Bullet *> & bullets) {}
   virtual void output() = 0;
   virtual void input(bool isUp, bool isDown, bool isB) {}
   virtual void move(std::list<Effect*> &effects);

protected:
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
         pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
   void drawLine(const Position& begin, const Position& end,
                 double red = 1.0, double green = 1.0, double blue = 1.0) const;

   void drawDot(const Position& point, double radius = 2.0,
                double red = 1.0, double green = 1.0, double blue = 1.0) const;
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1) {}
   
   void output();
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
   int timeToDie;
public:
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60) {}
   
   void output();
   void move(std::list<Effect*> & effects);
   void death(std::list<Bullet *> & bullets);
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   int timeToDie;
public:
   Shrapnel(const Bomb & bomb)
   {
      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();

      value = 0;
      
      radius = 3.0;
   }
   
   void output();  
   void move(std::list<Effect*> & effects);
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
public:
   Missile(double angle, double speed = 10.0) : Bullet(angle, speed, 1.0, 3) {}
   
   void output();
   void input(bool isUp, bool isDown, bool isB)
   {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }
   void move(std::list<Effect*> & effects);
};







// separation of concerns pattern stuff here
class BulletStorage
{
public:
   BulletStorage(double angle, double speed, double radius, int value);
   
   //getters
   Position getPoint()      { return pt;         }
   Position getDimensions() { return dimensions; }
   Velocity getVelocity()   { return v;          }
   double getRadius()       { return radius;     }
   int getValue()           { return value; }
   int getTimeToDie()       { return timeToDie;  }
   bool isDead()            { return dead; }
   
   //setters
   void setValue( int value )     { this->value = value; }
   void setPoint( const Position & pt ) { this->pt = pt;   }
   void setDead( bool isDead )    { this->dead = isDead; }
   void setTimeToDie( int time )  { this->timeToDie = time; }
//   void setVelocity( Velocity v ) { this->v = v; }
   
protected:
   static Position dimensions;
   Position pt;
   Velocity v;
   double radius;
   bool dead;
   int value;
   int timeToDie = 0;
};


class BulletLogic
{
public:
   BulletStorage storage;
   
   void kill() { storage.setDead(true); }
   void setValue(int newValue) { storage.setValue(newValue); }
   Position getPosition() { return storage.getPoint();     }
   Velocity getVelocity() { return storage.getVelocity();  }
   double getRadius()     { return storage.getRadius();    }
   Position getPoint()    { return storage.getPoint(); }
   int getValue()         { return storage.getValue(); }
   BulletStorage getStorage() const { return storage; }
   bool isDead()          { return storage.isDead(); }
   virtual void death(std::list<BulletStorage *> & bullets);
   virtual void move(std::list<Effect*> &effects);
   
   virtual BulletStorage createBulletStorage(double angle, double speed, double radius, int value);
   
protected:
   bool isOutOfBounds();
   //put random methods in here
   int    random(int    min, int    max);
   double random(double min, double max);
};


class BulletInterface
{
public:
   BulletLogic* logic;
   
   virtual void output() {};
   virtual void input(bool isUp, bool isDown, bool isB) {}
   
   
protected:
   void drawLine(const Position& begin, const Position& end, double red, double green, double blue) const;
   void drawDot(const Position& point, double radius, double red, double green, double blue) const;
};

/*********************
 * PELLET LOGIC
 * logic for a small little bullet
 **********************/
class PelletLogic : public BulletLogic
{
   BulletStorage createBulletStorage(double angle, double speed = 15.0, double radius = 1.0, int value = 1) override { return BulletStorage(angle, speed, radius, value); }
};

/*********************
 * BOMB LOGIC
 * logic for things that go "boom"
 **********************/
class BombLogic : public BulletLogic
{
   BulletStorage createBulletStorage(double angle, double speed = 10.0, double radius = 4.0, int value = 4) override { return BulletStorage(angle, speed, radius, value); storage.setTimeToDie(60); }
   
   void move(std::list<Effect*> & effects)   override;
   void death(std::list<BulletStorage *> & bullets);
};

/*********************
 * SHRAPNEL LOGIC
 * logic for a piece that broke off of a bomb
 **********************/
class ShrapnelLogic : public BulletLogic
{
   BulletStorage createBulletStorageForShrapnel(BulletStorage & bombStorage);
   void move(std::list<Effect*> & effects)   override;
};

/*********************
 * MISSILE LOGIC
 * logic for guided missiles
 **********************/
class MissileLogic : public BulletLogic
{
   BulletStorage createBulletStorage(double angle, double speed = 10.0, double radius = 1.0, int value = 3) override { return BulletStorage(angle, speed, radius, value); }

   void move(std::list<Effect*> & effects) override;
};

/*********************
 * Pellet Interface
 * People gotta be able to look at them pellets
 **********************/
class PelletInterface : public BulletInterface
{
public:
   void output() override;
};

/*********************
 * Bomb Interface
 * People gotta be able to look at them Bombs
 **********************/
class BombInterface : public BulletInterface
{
public:
   void output() override;
};

/*********************
 * Shrapnel Interface
 * People gotta be able to look at them Shrapnels
 **********************/
class ShrapnelInterface : public BulletInterface
{
public:
   void output() override;
};

/*********************
 * Missile Interface
 * People gotta be able to look at them Missiles
 **********************/
class MissileInterface : public BulletInterface
{
public:
   void input(bool isUp, bool isDown, bool isB)
   {
      if (isUp)
         logic->getVelocity().turn(0.04);
      if (isDown)
         logic->getVelocity().turn(-0.04);
   }
   
   void output() override;
};
