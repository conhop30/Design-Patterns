#pragma once

#include "abstractColleague.h"
#include <vector>

/**
* ENUM : MESSAGE
*/
enum Message { BIRD_DIED, BULLET_FIRED };

/*
* CLASS : MEDIATOR
*/
class Mediator
{
protected:
    std::vector<AbstractColleague*> colleagues;

public:
    void notify(Message message) {}
    void enroll(std::vector<AbstractColleague*> colleagues) {}
    void unenroll(std::vector<AbstractColleague*> colleagues) {}
};
