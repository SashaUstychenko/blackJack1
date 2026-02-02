#ifndef PLAYER_H
#define PLAYER_H
#include"gambler.h"

class Player : public Gambler
{
    private:
        int money = 0;
        int bet = 0;
    public:
        void placeBet(int amount);
        int getMoney()const;
        int getBet()const;
};

#endif // PLAYER_H
