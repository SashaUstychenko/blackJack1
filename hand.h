#ifndef HAND_H
#define HAND_H

#include"card.h"
#include"vector"

class Hand
{
    private:
        std::vector<Card> cards;
    public:
        void addCard(const Card& card);
        void clear();
        int score()const;
        bool isBust()const;
        bool isBlackJack()const;
        int cardCount()const;

        const std::vector<Card>&getGards()const;

};

#endif // HAND_H
