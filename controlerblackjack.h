#ifndef CONTROLERBLACKJACK_H
#define CONTROLERBLACKJACK_H

#include <QObject>
#include <QString>

#include"card.h"


class ControlerBlackJack : public QObject
{
        Q_OBJECT
    private:
        QString cardImagePath(const Card& card)const;
    public:
        explicit ControlerBlackJack(QObject *parent = nullptr);
        Q_INVOKABLE QString playerCardImage(int index)const;
        Q_INVOKABLE QString dealerCardImage(int index)const;

    signals:
};

#endif // CONTROLERBLACKJACK_H
