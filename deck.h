#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <memory.h>
#include <vector>
#include <QVector>
class Deck
{
    private:
    std::vector<Card>cards;

    public:
        void reset();
        void shuffle();
        Card draw();
        int size()const;


};

#endif // DECK_H
