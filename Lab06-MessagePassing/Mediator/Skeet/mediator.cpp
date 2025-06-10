
#include "mediator.h"
#include "abstractColleague.h"

void Mediator::notify(Message& message)
{
    for (int i = 0; i < colleagues.size(); i++)
        colleagues[i]->notify(message);
}