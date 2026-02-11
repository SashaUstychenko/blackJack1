#include "player.h"



Player::Player()
    : money(1000),bet(0)
{

}

void Player::placeBet(int amount)
{
    if (money >= amount)
    {
        bet = amount;
        money -= amount;
    }
}

void Player::placePerfectPairBet(int amount)
{
    if (amount <= 0)
        return;

    if (money >= amount)
    {
        perfectPairBet = amount;
        money -= amount;
    }
}

int Player::getPerfectPairBet() const
{
    return perfectPairBet;
}

int Player::getMoney() const
{
    return money;
}

int Player::getBet() const
{
    return bet;
}

void Player::updateMoney(int amount)
{
    money += amount;
}

void Player::clearBets()
{
    bet = 0;
    perfectPairBet = 0;
}

