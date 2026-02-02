#ifndef GAMBLER_H
#define GAMBLER_H
#include"hand.h"
class Gambler
{
    protected:
        Hand hand;

    public:
        virtual ~Gambler()= default;
        const Hand& hetHand()const;
        Hand& getHand();
        void clearHand();
};

#endif // GAMBLER_H
