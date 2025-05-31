#include "scoreColleague.h"
#include "score.h"

void ScoreColleague::notify(Message & message)
{
    pStatus->adjust(message.value);
}