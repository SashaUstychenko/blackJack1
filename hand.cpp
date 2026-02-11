#include "hand.h"


void Hand::addCard(const Card &card)
{
    cards.push_back(card);
}

void Hand::clear()
{
    cards.clear();
}

int Hand::score() const
{
    int totalScore = 0;
    int aceScore = 0; // ACE = 11 OR 1

    for(const auto& card : cards)
    {
        int cardValue = static_cast<int>(card.getRank());
        if(card.getRank() >= Rank::Jack)
        {
            cardValue = 10;
        }
        else if(card.getRank() == Rank::Ace)
        {
            cardValue = 11;
            ++aceScore;
        }
        totalScore += cardValue;
    }
    while(totalScore > 21 && aceScore > 0)
    {
        totalScore -= 10;
        --aceScore;
    }
    return totalScore;
}

bool Hand::isBust() const
{
    return score() > 21;
}

bool Hand::isBlackJack() const
{
    return cardCount() == 2;
}

int Hand::cardCount() const
{
    return cards.size();
}

const std::vector<Card>& Hand::getGards() const
{
    return cards;
}
























