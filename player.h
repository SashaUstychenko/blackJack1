#ifndef PLAYER_H
#define PLAYER_H
#include"gambler.h"

class Player : public Gambler
{
    private:
        int money = 0;
        int bet = 0;
        int perfectPairBet = 0;
    public:
        void placeBet(int amount);
        void placePerfectPairBet(int amount);
        int getPerfectPairBet() const;
        int getMoney()const;
        int getBet()const;
        void updateMoney(int amount);
        void clearBets();
};

#endif // PLAYER_H
