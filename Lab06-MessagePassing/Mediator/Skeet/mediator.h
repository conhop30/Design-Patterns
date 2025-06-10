#pragma once

#include <vector>

class AbstractColleague;

/**
* ENUM : MESSAGE TYPE
*/
enum MessageType { BIRD_DIED, BULLET_FIRED };

/**
* STRUCT : MESSAGE
*/
struct Message { MessageType type; int value; };

/*
* CLASS : MEDIATOR
*/
class Mediator
{
protected:
    std::vector<AbstractColleague*> colleagues;

public:
    void notify(Message & message);
    void enroll(std::vector<AbstractColleague*> colleagues) {}
    void unenroll(std::vector<AbstractColleague*> colleagues) {}
};
