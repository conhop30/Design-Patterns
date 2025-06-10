#pragma once

// Forward declarations
class Mediator;
struct Message;

/*
* CLASS : ABSTRACT COLLEAGUE
*/
class AbstractColleague
{
protected:
    Mediator* mediator;

public:
    virtual void notify(Message & message) = 0;
    void enroll(Mediator & mediator);
    void unenroll(Mediator & mediator);
};