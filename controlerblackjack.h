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
public:

    enum class RoundResult {
        None,
        PlayerWin,
        DealerWin,
        Push,
        PlayerBust,
        DealerBust,
        BlackJack
    };
    Q_ENUM(RoundResult)
    enum class PerfectPairResult {
        None,
        Win,
        Lose
    };
    Q_ENUM(PerfectPairResult)
private:
    Deck deck;
    Player player;
    Dealer dealer;
    RoundResult roundResult = RoundResult::None;
    PerfectPairResult perfectPairResult = PerfectPairResult::None;


    bool roundFinished = false;
    bool dealerHiddenCard = true;
    bool doubleDownEnabled = true;
    bool firstPlayerAction = true;
    bool blackjackPays3_2 = true;
    bool perfectPairsEnabled = true;
    bool betPlaced = false;

    int perfectPairPayout = 10; // 10:1

    void checkPerfectPair();


    QString cardImagePath(const Card& card) const;
    QString rankToString(Rank rank) const;
    QString suitToString(Suit suit) const;

    void checkRoundEnd();
    bool isPerfectPair() const;

public:



    explicit ControlerBlackJack(QObject *parent = nullptr);

    Q_PROPERTY(RoundResult roundResult READ getRoundResult NOTIFY roundResultChanged)
    Q_PROPERTY(bool perfectPairEnabled READ canPlacePerfectPairBet NOTIFY perfectPairChanged)
    Q_PROPERTY(bool dealerHiddenCard READ isDealerHidden NOTIFY dealerHiddenCardChanged)
    Q_PROPERTY(PerfectPairResult perfectPairResult READ getPerfectPairResult NOTIFY perfectPairResultChanged)
    Q_PROPERTY(bool perfectPairWin READ isPerfectPairWin NOTIFY perfectPairResultChanged)
    Q_PROPERTY(bool perfectPairEnabled READ canPlacePerfectPairBet NOTIFY perfectPairChanged)

    Q_PROPERTY(int dealerVisibleScore READ dealerVisibleScore NOTIFY dealerHandChanged)
    Q_PROPERTY(int playerScore READ playerScore NOTIFY playerHandChanged)


    Q_PROPERTY(int playerCardCount READ playerCardCount NOTIFY playerHandChanged)
    Q_PROPERTY(int dealerCardCount READ dealerCardCount NOTIFY dealerHandChanged)

    Q_PROPERTY(int playerMoney READ playerMoney NOTIFY playerMoneyChanged)
    Q_PROPERTY(int playerBet READ playerBet NOTIFY playerBetChanged)

     RoundResult getRoundResult() const;

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
    Q_INVOKABLE int dealerVisibleScore() const;


    Q_INVOKABLE int playerMoney() const;
    Q_INVOKABLE int playerBet() const;
    Q_INVOKABLE void placeBet(int amount);

    Q_INVOKABLE bool canDoubleDown() const;
    Q_INVOKABLE void doubleDown();

    Q_INVOKABLE bool canPlacePerfectPairBet() const;
    Q_INVOKABLE void placePerfectPairBet(int amount);
    PerfectPairResult getPerfectPairResult() const;
    Q_INVOKABLE bool isPerfectPairWin() const;


    Q_INVOKABLE bool canPlayerHit();
    Q_INVOKABLE bool isRoundFinished() const;

    Q_INVOKABLE bool canStartRound() const;
    Q_INVOKABLE bool isDealerHidden()const;
    Q_INVOKABLE void revealDealerCard();




signals:
    void playerHandChanged();
    void dealerHandChanged();
    void playerMoneyChanged();
    void playerBetChanged();
    void roundResultChanged();
    void perfectPairResultChanged();
    void perfectPairChanged();
    void dealerHiddenCardChanged();




};

#endif // CONTROLERBLACKJACK_H
