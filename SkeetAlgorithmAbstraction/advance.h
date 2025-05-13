#pragma once
#include "bird.h"

class Advance
{
public:
    virtual void advance(Bird& bird, int points) = 0;
};
