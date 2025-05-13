#pragma once
#include "bird.h"

class Bird;

class Advance
{
public:
    virtual void advance(Bird & bird, int points) = 0;
};
