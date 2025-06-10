//
//  flyingObject.h
//  Lab03
//
//  Created by William Barr on 5/27/25.
//
#pragma once

#include "visitor.h"


class FlyingObject {
public:
   virtual void accept(Visitor & visitor) = 0;
};
