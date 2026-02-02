#include "deck.h"
#include <algorithm>
#include <QRandomGenerator>

void Deck::reset()
{
    cards.clear();
    cards.reserve(52);

    for(int s = static_cast<int>(Suit::Hearts); s <= static_cast<int>(Suit::Clubs); ++s)
    {
        for(int r = static_cast<int>(Rank::Ace); r <= static_cast<int>(Rank::King); ++r)
        {
            Suit suit = static_cast<Suit>(s);
            Rank rank = static_cast<Rank>(r);
            cards.push_back(Card(suit, rank));
        }
    }
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(cards.begin(),cards.end(),gen);
}

Card Deck::draw()
{
    if(cards.empty())
    {
        reset();
        shuffle();
    }
    Card card = cards.back();
    cards.pop_back();
    return card;
}

int Deck::size() const
{
    return cards.size();
}

