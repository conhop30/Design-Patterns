#pragma once

#include "hitRatioColleague.h"
#include "score.h"

void HitRatioColleague::notify(Message& message)
{
    if (message.type == BIRD_DIED)
        pStatus->adjust(message.value);
}