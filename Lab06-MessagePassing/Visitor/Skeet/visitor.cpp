//
//  visitor.cpp
//  Lab03
//
//  Created by William Barr on 5/29/25.
//
#pragma once

#include "visitor.h"
#include "bird.h"
#include "bullet.h"
#include "effect.h"

void VisitorDraw :: visit(Bird & bird)
{
   bird.draw();
}
void VisitorDraw :: visit(Bullet & bullet)
{
   bullet.output();
}
void VisitorDraw :: visit(Effect & effect)
{
   effect.render();
}
