
#include "dealer.h"

bool Dealer::shouldDraw() const
{
    int score = hand.score();

    return score < 17;
}
