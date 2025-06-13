/***********************************************************************
 * Source File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#include "bullet.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

/*********************************************
 * BULLET constructor
 *********************************************/
Bullet::Bullet(double angle, double speed, double radius, int value) :
   dead(false), radius(radius), value(value)
{
   // set the initial position
   pt.setX(dimensions.getX() - 1.0);
   pt.setY(1.0);
   assert(pt.getX() > 100.0);

   // set the initial velocity
   v.setDx(-speed * cos(angle));
   v.setDy(speed * sin(angle));
   assert(v.getDx() <= 0.0);
   assert(v.getDy() >= 0.0);
}

/*********************************************
 * BOMB DEATH
 * Bombs have a tendency to explode!
 *********************************************/
void Bomb::death(std::list<Bullet*>& bullets)
{
   for (int i = 0; i < 20; i++)
      bullets.push_back(new Shrapnel(*this));
}

 /***************************************************************/
 /***************************************************************/
 /*                             MOVE                            */
 /***************************************************************/
 /***************************************************************/

/*********************************************
 * BULLET MOVE
 * Move the bullet along by one time period
 *********************************************/
void Bullet::move(std::list<Effect*> & effects)
{
   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
      kill();
}

/*********************************************
 * BOMB MOVE
 * Move the bomb along by one time period
 *********************************************/
void Bomb::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    timeToDie--;
    if (!timeToDie)
        kill();

    // do the inertia thing
    Bullet::move(effects);
}

/*********************************************
 * MISSILE MOVE
 * Move the missile along by one time period
 *********************************************/
void Missile::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
   effects.push_back(new Exhaust(pt, v));

    // do the inertia thing
    Bullet::move(effects);
}

/*********************************************
 * SHRAPNEL MOVE
 * Move the shrapnel along by one time period
 *********************************************/
void Shrapnel::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    timeToDie--;
    if (!timeToDie)
        kill();

    // add a streek
    effects.push_back(new Streek(pt, v));
    
    // do the usual bullet stuff (like inertia)
    Bullet::move(effects);
}

/***************************************************************/
/***************************************************************/
/*                            OUTPUT                           */
/***************************************************************/
/***************************************************************/

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void Bullet::drawLine(const Position& begin, const Position& end,
                      double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void Bullet::drawDot(const Position& point, double radius,
                     double red, double green, double blue) const
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*********************************************
 * PELLET OUTPUT
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void Pellet::output()
{
   if (!isDead())
      drawDot(pt, 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * BOMB OUTPUT
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void Bomb::output()
{
   if (!isDead())
   {
       // Bomb actually has a gradient to cut out the harsh edges
       drawDot(pt, radius + 2.0, 0.50, 0.50, 0.00);
       drawDot(pt, radius + 1.0, 0.75, 0.75, 0.00);
       drawDot(pt, radius + 0.0, 0.87, 0.87, 0.00);
       drawDot(pt, radius - 1.0, 1.00, 1.00, 0.00);
   }
}

/*********************************************
 * SHRAPNEL OUTPUT
 * Draw a fragment - a bright yellow dot
 *********************************************/
void Shrapnel::output()
{
    if (!isDead())
       drawDot(pt, radius, 1.0, 1.0, 0.0);
}

/*********************************************
 * MISSILE OUTPUT
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void Missile::output()
{
    if (!isDead())
    {
        // missile is a line with a dot at the end so it looks like fins.
        Position ptNext(pt);
        ptNext.add(v);
        drawLine(pt, ptNext, 1.0, 1.0, 0.0);
        drawDot(pt, 3.0, 1.0, 1.0, 1.0);
    }
}

/***************************************************************/
/***************************************************************/
/*                             MISC.                           */
/***************************************************************/
/***************************************************************/

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
int Bullet::random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double Bullet::random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}



/******************************************************************
 * Separation of Concerns bullet stuff here now
 * This is where we be putting the new methods and stuff I guess
 ****************************************************************/

/******************************************************************
 * BulletStorage constructor
 * default constructor
 ****************************************************************/
BulletStorage::BulletStorage(double angle, double speed, double radius, int value) :
   dead(false), radius(radius), value(value)
{
   // set the initial position
   pt.setX(dimensions.getX() - 1.0);
   pt.setY(1.0);
   assert(pt.getX() > 100.0);

   // set the initial velocity
   v.setDx(-speed * cos(angle));
   v.setDy(speed * sin(angle));
   assert(v.getDx() <= 0.0);
   assert(v.getDy() >= 0.0);
}


// Bullet logic

/******************************************************************
 * create an instance of bullet storage
 * store the bullet
 ****************************************************************/
BulletStorage BulletLogic::createBulletStorage(double angle, double speed, double radius, int value)
{
   return BulletStorage(angle, speed, radius, value);
}

/******************************************************************
 * DEATH
 * kill the bullet
 ****************************************************************/
void BulletLogic::death(std::list<Bullet*> & bullets)
{
   this->storage.setDead(true);
}

/******************************************************************
 * ISOUTOFBOUNDS
 * checks to see if the bullet is out of bounds
 ****************************************************************/
bool BulletLogic::isOutOfBounds()
{
   Position pt = storage.getPoint();
   
   return (pt.getX() < -storage.getRadius()
           || pt.getX() >= storage.getDimensions().getX() + storage.getRadius()
           || pt.getY() < -storage.getRadius()
           || pt.getY() >= storage.getDimensions().getY() + storage.getRadius());
}


/******************************************************************
 * Move
 * move the bullet
 ****************************************************************/
void BulletLogic::move(std::list<Effect*> &effects)
{
   // inertia
   Position pt = storage.getPoint();
   pt.add(storage.getVelocity());
   storage.setPoint(pt);
   
   // out of bounds checker
      if (isOutOfBounds())
         kill();
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
int BulletLogic::random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double BulletLogic::random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}


/*********************************************
 * BOMB LOGIC MOVE
 * Move the bomb along by one time period
 *********************************************/
void BombLogic::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    storage.setTimeToDie(storage.getTimeToDie() - 1);
    if (!storage.getTimeToDie())
        kill();

    // do the inertia thing
    BulletLogic::move(effects);
}

/*********************************************
 * BOMB LOGIC DEATH
 * Bombs have a tendency to explode! coolbeans
 *********************************************/
void BombLogic::death(std::list<BulletStorage*>& bullets)
{
   for (int i = 0; i < 20; i++)
      {
         BulletStorage* bullet = new BulletStorage(random(0.0, 6.2),
                                                   random(10.0, 15.0),
                                                   3.0,
                                                   0);
         bullet->setPoint(storage.getPoint());
         bullets.push_back(bullet);
      }

}

/*********************************************
 * SHRAPNEL CREATION
 * the bomb shrapnel has to be made
 *********************************************/
BulletStorage ShrapnelLogic::createBulletStorageForShrapnel(BulletStorage & bombStorage)
{
   BulletStorage bullet(random(0.0, 6.2),
                        random(10.0, 15.0),
                        3.0,
                        0);
   bullet.setPoint(bombStorage.getPoint());
   return bullet;
}

/*********************************************
 * SHRAPNEL LOGIC MOVE
 * Move the shrapnel along by one time period
 *********************************************/
void ShrapnelLogic::move(std::list<Effect*> & effects)
{
    // kill if it has been around too long
    storage.setTimeToDie(storage.getTimeToDie() - 1);
    if (!storage.getTimeToDie())
        kill();
   
   // add a streek
   effects.push_back(new Streek(storage.getPoint(), storage.getVelocity()));

   // do the inertia thing
   BulletLogic::move(effects);
}

/*********************************************
 * MISSILE LOGIC MOVE
 * Move the Missile along by one time period
 *********************************************/
void MissileLogic::move(std::list<Effect*> & effects)
{
   // kill if it has been around too long
   effects.push_back(new Exhaust(storage.getPoint(), storage.getVelocity()));
   
   // do the inertia thing
   BulletLogic::move(effects);
}



//bullet interface stuff

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void BulletInterface::drawLine(const Position& begin, const Position& end,
                      double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void BulletInterface::drawDot(const Position& point, double radius,
                     double red, double green, double blue) const
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*********************************************
 * PELLET OUTPUT
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void PelletInterface::output()
{
   if (!logic.isDead())
      drawDot(logic.getPoint(), 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * BOMB OUTPUT
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void BombInterface::output()
{
   if (!logic.isDead())
   {
       // Bomb actually has a gradient to cut out the harsh edges
       drawDot(logic.getPoint(), logic.getRadius() + 2.0, 0.50, 0.50, 0.00);
       drawDot(logic.getPoint(), logic.getRadius() + 1.0, 0.75, 0.75, 0.00);
       drawDot(logic.getPoint(), logic.getRadius() + 0.0, 0.87, 0.87, 0.00);
       drawDot(logic.getPoint(), logic.getRadius() - 1.0, 1.00, 1.00, 0.00);
   }
}

/*********************************************
 * SHRAPNEL OUTPUT
 * Draw a fragment - a bright yellow dot
 *********************************************/
void ShrapnelInterface::output()
{
    if (!logic.isDead())
       drawDot(logic.getPoint(), logic.getRadius(), 1.0, 1.0, 0.0);
}

/*********************************************
 * MISSILE OUTPUT
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void MissileInterface::output()
{
    if (!logic.isDead())
    {
        // missile is a line with a dot at the end so it looks like fins.
        Position ptNext(logic.getPoint());
        ptNext.add(logic.getVelocity());
        drawLine(logic.getPoint(), ptNext, 1.0, 1.0, 0.0);
        drawDot(logic.getPoint(), 3.0, 1.0, 1.0, 1.0);
    }
}
