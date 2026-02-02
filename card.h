#ifndef CARD_H
#define CARD_H

enum class Suit
{
    Hearts,
    Spades,
    Diamonds,
    Clubs
};

enum class Rank
{
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

class Card
{
    private:
        Suit suit;
        Rank rank;

    public:

        Card(Suit suit,Rank rank);
        Suit getSuit()const
        {
            return suit;
        }
        Rank getRank()const
        {
            return rank;
        }
};

#endif // CARD_H
