//
//  visitor.h
//  Lab03
//
//  Created by William Barr on 5/28/25.
//

#pragma once


class Bird;
class Bullet;
class Effect;


class Visitor
{
public:
   virtual void visit(Bird & bird)     = 0;
   virtual void visit(Bullet & bullet) = 0;
   virtual void visit(Effect & effect) = 0;
};

class VisitorDraw : public Visitor
{
public:
   virtual void visit(Bird & bird);
   virtual void visit(Bullet & bullet);
   virtual void visit(Effect & effect);
};
