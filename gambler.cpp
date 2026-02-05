#include "gambler.h"


const Hand &Gambler::getHand() const
{
    return hand;
}

Hand &Gambler::getHand()
{
    return hand;
}

void Gambler::clearHand()
{
    hand.clear();
}
