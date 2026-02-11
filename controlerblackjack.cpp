#include "controlerblackjack.h"
#include <QDebug>



ControlerBlackJack::ControlerBlackJack(QObject *parent)
    : QObject{parent}
{}

void ControlerBlackJack::startGame()
{
    qDebug() << "startGame called:" ;



    qDebug() << "startGame called:b";
    player.clearHand();
    dealer.clearHand();

    deck.reset();
    deck.shuffle();

    firstPlayerAction = true;
    roundFinished = false;



    player.getHand().addCard(deck.draw());
    dealer.getHand().addCard(deck.draw());
    player.getHand().addCard(deck.draw());

    dealer.getHand().addCard(deck.draw());

    emit playerHandChanged();
    emit dealerHandChanged();

    qDebug() << "startGame called: end" ;


}

void ControlerBlackJack::playerHit()
{
    if (roundFinished)
        return;
    firstPlayerAction = false;

    player.getHand().addCard(deck.draw());

    if (player.getHand().isBust())
        checkRoundEnd();
}

void ControlerBlackJack::playerStand()
{
    firstPlayerAction = false;
    while(dealer.shouldDraw() && deck.size()>0)
    dealer.getHand().addCard(deck.draw());

    roundFinished = true;
}

void ControlerBlackJack::newRound()
{
    if (deck.size() < 10)
    {
        deck.reset();
        deck.shuffle();
    }

    player.clearHand();
    dealer.clearHand();

    roundFinished = false;
    firstPlayerAction = true;

    player.getHand().addCard(deck.draw());
    dealer.getHand().addCard(deck.draw());

    player.getHand().addCard(deck.draw());
    dealer.getHand().addCard(deck.draw());
    if (perfectPairsEnabled && player.getPerfectPairBet() > 0)
    {
        if (isPerfectPair())
        {
            int win = player.getPerfectPairBet() * perfectPairPayout;
            player.updateMoney(player.getPerfectPairBet() + win);
        }
    }
    checkRoundEnd();
}


QString ControlerBlackJack::playerCardImage(int index) const
{
    qDebug() << "playerCardImage called index:" << index;

    const auto& cards = player.getHand().getGards();
    if (index < 0 || index >= static_cast<int>(cards.size()))
        return "";

    return cardImagePath(cards[index]);
}

QString ControlerBlackJack::dealerCardImage(int index) const
{
    qDebug() << "dealer CardImage called index:" << index;

    const auto& cards = dealer.getHand().getGards();
    if (index < 0 || index >= static_cast<int>(cards.size()))
        return "";

    return cardImagePath(cards[index]);;
}

int ControlerBlackJack::playerCardCount() const
{
    return player.getHand().cardCount();
}

int ControlerBlackJack::dealerCardCount() const
{
    return dealer.getHand().cardCount();
}

int ControlerBlackJack::playerScore() const
{
    return player.getHand().score();
}

int ControlerBlackJack::dealerScore() const
{
    return dealer.getHand().score();
}

int ControlerBlackJack::playerMoney() const
{
    return player.getMoney();
}

int ControlerBlackJack::playerBet() const
{
    return player.getBet();
}

void ControlerBlackJack::placeBet(int amount)
{
    qDebug() << "placeBet called:" << amount;

    player.placeBet(amount);
    startGame();
}

bool ControlerBlackJack::canDoubleDown() const
{
    return doubleDownEnabled
           && firstPlayerAction
           && player.getMoney() >= player.getBet()
           && !roundFinished;

}

void ControlerBlackJack::doubleDown()
{
   if (!canDoubleDown())
            return;

    player.placeBet(player.getBet());

    player.getHand().addCard(deck.draw());

    firstPlayerAction = false;

    while (dealer.shouldDraw())
    {
        dealer.getHand().addCard(deck.draw());
    }
    checkRoundEnd();
}

bool ControlerBlackJack::canPlacePerfectPairBet() const
{
    return perfectPairsEnabled
           && !roundFinished
           && player.getHand().cardCount() == 0
           && player.getMoney() > 0;
}

void ControlerBlackJack::placePerfectPairBet(int amount)
{
    if (!canPlacePerfectPairBet())
        return;

    player.placePerfectPairBet(amount);
}

bool ControlerBlackJack::canPlayerHit()
{
    if(roundFinished == false && !player.getHand().isBust())
    {
        return true;
    }
    return false;
}

bool ControlerBlackJack::isRoundFinished() const
{
    return roundFinished;
}

bool ControlerBlackJack::canStartRound() const
{
    return betPlaced && !roundFinished;
}
QString ControlerBlackJack::cardImagePath(const Card &card) const
{
     qDebug() << "cardImagePath called for card:" ;
    return QString("qrc:/image/%1_of_%2.png").arg(rankToString(card.getRank()))
                                            .arg(suitToString(card.getSuit()));

}

QString ControlerBlackJack::rankToString(Rank rank) const
{
    switch (rank)
    {
    case Rank::Ace:   return "ace";
    case Rank::Two:   return "2";
    case Rank::Three: return "3";
    case Rank::Four:  return "4";
    case Rank::Five:  return "5";
    case Rank::Six:   return "6";
    case Rank::Seven: return "7";
    case Rank::Eight: return "8";
    case Rank::Nine:  return "9";
    case Rank::Ten:   return "10";
    case Rank::Jack:  return "jack";
    case Rank::Queen: return "queen";
    case Rank::King:  return "king";
    }
    return "";
}
QString ControlerBlackJack::suitToString(Suit suit) const
{
    switch (suit)
    {
    case Suit::Hearts:   return "hearts";
    case Suit::Spades:   return "spades";
    case Suit::Diamonds: return "diamonds";
    case Suit::Clubs:    return "clubs";
    }
    return "";
}

void ControlerBlackJack::checkRoundEnd()
{
    int pScore = playerScore();
    int dScore = dealerScore();

    if(pScore > 21 )
    {
        player.updateMoney(0);
    }
    else if(dScore > 21)
    {
        player.updateMoney(player.getBet()*2);
    }
    else if(pScore>dScore)
    {
        player.updateMoney(player.getBet()*2);
    }
    else if(player.getHand().isBlackJack())
    {
        if (blackjackPays3_2)
        {
            int win = player.getBet() * 3 / 2;
            player.updateMoney(player.getBet() + win);
        }
        else
        {
            player.updateMoney(player.getBet() * 2);
        }
    }
    else if(dScore>pScore)
    {
        player.updateMoney(0);
    }
    else
    {
        player.updateMoney(player.getBet());
    }
    player.placeBet(0);

    roundFinished = true;
    player.clearBets();
}

bool ControlerBlackJack::isPerfectPair() const
{
    const auto& cards = player.getHand().getGards();

    if (cards.size() != 2)
        return false;

    return cards[0].getRank() == cards[1].getRank();
}





















