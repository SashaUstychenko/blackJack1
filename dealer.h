#ifndef DEALER_H
#define DEALER_H

#include"gambler.h"

class Dealer:public Gambler
{
    public:
    bool shouldDraw()const;

};

#endif // DEALER_H
