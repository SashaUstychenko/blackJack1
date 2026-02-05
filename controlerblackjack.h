#ifndef CONTROLERBLACKJACK_H
#define CONTROLERBLACKJACK_H

#include <QObject>
#include <QString>

#include "player.h"
#include "dealer.h"
#include "deck.h"

class ControlerBlackJack : public QObject
{
    Q_OBJECT

private:
    Deck deck;
    Player player;
    Dealer dealer;

    bool roundFinished = false;
    bool dealerHiddenCard = true;
    bool doubleDownEnabled = true;
    bool firstPlayerAction = true;
    bool blackjackPays3_2 = true;
    bool perfectPairsEnabled = true;

    int perfectPairPayout = 10; // 10:1


    QString cardImagePath(const Card& card) const;
    QString rankToString(Rank rank) const;
    QString suitToString(Suit suit) const;

    void checkRoundEnd();
    bool isPerfectPair() const;

public:
    explicit ControlerBlackJack(QObject *parent = nullptr);

    // actions from UI
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void playerHit();
    Q_INVOKABLE void playerStand();
    Q_INVOKABLE void newRound();

    // data for UI
    Q_INVOKABLE QString playerCardImage(int index) const;
    Q_INVOKABLE QString dealerCardImage(int index) const;

    Q_INVOKABLE int playerCardCount() const;
    Q_INVOKABLE int dealerCardCount() const;

    Q_INVOKABLE int playerScore() const;
    Q_INVOKABLE int dealerScore() const;

    Q_INVOKABLE int playerMoney() const;
    Q_INVOKABLE int playerBet() const;
    Q_INVOKABLE void placeBet(int amount);

    Q_INVOKABLE bool canDoubleDown() const;
    Q_INVOKABLE void doubleDown();

    Q_INVOKABLE bool canPlacePerfectPairBet() const;
    Q_INVOKABLE void placePerfectPairBet(int amount);


    Q_INVOKABLE bool canPlayerHit();
    Q_INVOKABLE bool isRoundFinished() const;
};

#endif // CONTROLERBLACKJACK_H
