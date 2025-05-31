#include "abstractColleague.h"
#include "mediator.h"

void AbstractColleague::enroll(Mediator & enrollee)
{
    this->mediator = mediator;
}