#pragma once

#include "abstractColleague.h"
#include "mediator.h"

class Bird;

class BirdColleague : AbstractColleague
{
private:
    Message* message = new Message;
    Bird* pBird;

public:
    void wentOutOfBounds();
    void wasShot();
    virtual void notify(Message& message) { }
};
