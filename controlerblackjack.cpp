#include "controlerblackjack.h"
#include <QDebug>



ControlerBlackJack::ControlerBlackJack(QObject *parent)
    : QObject{parent}
{}

ControlerBlackJack::RoundResult ControlerBlackJack::getRoundResult() const
{
    return roundResult;
}

void ControlerBlackJack::startGame()
{
    qDebug() << "startGame called:" ;
    roundResult = RoundResult::None;
    emit roundResultChanged();

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
    checkPerfectPair();


    emit playerHandChanged();
    emit dealerHandChanged();
}

void ControlerBlackJack::playerHit()
{
    qDebug() << "player s" ;
    if (roundFinished)
        return;
    firstPlayerAction = false;

    player.getHand().addCard(deck.draw());

    if (player.getHand().isBust())
        checkRoundEnd();
    qDebug() << "player e" ;
    emit playerHandChanged();

}

void ControlerBlackJack::playerStand()
{
    if (roundFinished)
        return;

    firstPlayerAction = false;

    while (dealer.shouldDraw() && deck.size() > 0) {
        dealer.getHand().addCard(deck.draw());
    }
    dealerHiddenCard = false;
    emit dealerHandChanged();

    checkRoundEnd();
}

void ControlerBlackJack::newRound()
{
    perfectPairResult = PerfectPairResult::None;
    emit perfectPairResultChanged();
    perfectPairsEnabled = true;
    emit perfectPairChanged();

    roundResult = RoundResult::None;
    emit roundResultChanged();

    if (deck.size() < 10)
    {
        deck.reset();
        deck.shuffle();
    }
    player.clearHand();
    dealer.clearHand();

    roundFinished = false;
    firstPlayerAction = true;

    perfectPairsEnabled = true;
    player.placePerfectPairBet(0);

    dealerHiddenCard = true;

    emit playerHandChanged();
    emit dealerHandChanged();
    emit playerMoneyChanged();
    emit playerBetChanged();
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

int ControlerBlackJack::dealerVisibleScore() const
{
    const auto& cards = dealer.getHand().getGards();
    if (cards.empty())
        return 0;

    if (dealerHiddenCard && cards.size() > 1)
    {
        Hand tempHand;
        tempHand.addCard(cards[0]);
        return tempHand.score();
    }
    else
    {
        return dealerScore();
    }
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
    emit playerBetChanged();
    emit playerMoneyChanged();
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

    emit playerHandChanged();
    emit playerMoneyChanged();
    emit playerBetChanged();
    while (dealer.shouldDraw() && deck.size() > 0)
    {
        dealer.getHand().addCard(deck.draw());
    }

    emit dealerHandChanged();
    checkRoundEnd();
}


bool ControlerBlackJack::canPlacePerfectPairBet() const
{
    return perfectPairsEnabled
           && !roundFinished
           && player.getHand().cardCount() == 0
           && player.getMoney() > 0
           && player.getPerfectPairBet() == 0;;
}

void ControlerBlackJack::placePerfectPairBet(int amount)
{
    if (!canPlacePerfectPairBet())
        return;

    if (amount <= 0 || amount > player.getMoney())
        return;
    player.placePerfectPairBet(amount);

    perfectPairsEnabled = false;

    emit playerMoneyChanged();
    emit playerBetChanged();
    emit perfectPairChanged();
}

ControlerBlackJack::PerfectPairResult
ControlerBlackJack::getPerfectPairResult() const
{
    return perfectPairResult;
}


bool ControlerBlackJack::isPerfectPairWin() const
{
    return perfectPairResult == PerfectPairResult::Win;
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

bool ControlerBlackJack::isDealerHidden() const
{
    return dealerHiddenCard;
}

void ControlerBlackJack::revealDealerCard()
{
    dealerHiddenCard = false;
    emit dealerHandChanged();
}


void ControlerBlackJack::checkPerfectPair()
{
    if (!perfectPairsEnabled)
        return;
    if (player.getPerfectPairBet() <= 0)
        return;
    if (player.getHand().cardCount() != 2)
        return;
    if (isPerfectPair())
    {
        perfectPairResult = PerfectPairResult::Win;

        int win = player.getPerfectPairBet() * perfectPairPayout;
        player.updateMoney(player.getPerfectPairBet() + win);
    }
    else
    {
        perfectPairResult = PerfectPairResult::Lose;
    }

    emit perfectPairResultChanged();
    emit playerMoneyChanged();
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

    bool playerBlackjack = player.getHand().isBlackJack();
    bool dealerBlackjack = dealer.getHand().isBlackJack();

    if (pScore > 21)
    {
        roundResult = RoundResult::PlayerBust;
        player.updateMoney(0);
    }
    else if (dScore > 21)
    {
        roundResult = RoundResult::DealerBust;
        player.updateMoney(player.getBet() * 2);
    }
    else if (playerBlackjack && dealerBlackjack)
    {
        roundResult = RoundResult::Push;
        player.updateMoney(player.getBet());
    }
    else if (playerBlackjack)
    {
        roundResult = RoundResult::BlackJack;
        int win = blackjackPays3_2 ? player.getBet() * 3 / 2 : player.getBet();
        player.updateMoney(player.getBet() + win);
    }
    else if (dealerBlackjack)
    {
        roundResult = RoundResult::DealerWin;
        player.updateMoney(0);
    }
    else if (pScore > dScore)
    {
        roundResult = RoundResult::PlayerWin;
        player.updateMoney(player.getBet() * 2);
    }
    else if (dScore > pScore)
    {
        roundResult = RoundResult::DealerWin;
        player.updateMoney(0);
    }
    else
    {
        roundResult = RoundResult::Push;
        player.updateMoney(player.getBet());
    }

    roundFinished = true;
    player.placeBet(0);

    emit roundResultChanged();
    emit playerMoneyChanged();
    emit playerBetChanged();
}

bool ControlerBlackJack::isPerfectPair() const
{
    const auto& cards = player.getHand().getGards();

    if (cards.size() != 2)
        return false;

    return cards[0].getRank() == cards[1].getRank();
}
























