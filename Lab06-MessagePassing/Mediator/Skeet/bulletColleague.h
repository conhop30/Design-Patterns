#pragma once

#include "abstractColleague.h"
#include "mediator.h"

class Bullet;

class BulletColleague : AbstractColleague
{
private:
    Message* status = new Message;
    Bullet* pBullet;
public:
    void firedBullet();
    virtual void notify(Message& message) { }
};

