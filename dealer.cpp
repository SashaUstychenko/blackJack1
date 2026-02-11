
#include "dealer.h"


bool Dealer::shouldDraw() const
{
    if(hand.score() < 17)
    {
        return true;
    }
    return false;
}
