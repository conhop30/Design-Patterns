#pragma once

#include "abstractColleague.h"
#include "mediator.h"

class Status;

class HitRatioColleague : AbstractColleague
{
private:
    Message* message = new Message;
    Status* pStatus;

public:
    virtual void notify(Message& message);
};

