#include "CoinFlip.h"

CoinFlip::CoinFlip()
    : gameActive(false), currentBet(0), betOnHeads(false),
      totalRounds(0), totalWagered(0), totalWon(0), lastResult(-1),
      gen(rd()), dist(0, 1) {} // 0 = tails, 1 = heads

void CoinFlip::startGame(std::shared_ptr<Player> player)
{
    currentPlayer = player;
    gameActive = true;
    totalRounds = 0;
    totalWagered = 0;
    totalWon = 0;
}

void CoinFlip::playRound()
{
    if (!gameActive || currentBet <= 0)
        return;

    int result = flipCoin();
    bool win = (result == 1 && betOnHeads) || (result == 0 && !betOnHeads);

    payout(win);
    totalRounds++;
}

void CoinFlip::endGame()
{
    gameActive = false;
    currentPlayer.reset();
    currentBet = 0;
}

bool CoinFlip::placeBet(double amount, bool betHeads)
{
    if (!gameActive || amount <= 0)
        return false;

    // Deduct the bet amount immediately
    if (!currentPlayer->withdraw(amount))
    {
        return false; // Insufficient funds
    }

    currentBet = amount;
    betOnHeads = betHeads;
    totalWagered += amount;
    return true;
}

int CoinFlip::flipCoin()
{
    lastResult = dist(gen); // 0 = tails, 1 = heads
    return lastResult;
}

void CoinFlip::payout(bool won)
{
    if (won)
    {
        double winnings = currentBet * 1.95; // Pays 1.95x the bet
        currentPlayer->deposit(winnings);
        totalWon += winnings;
    }
    currentBet = 0; // Reset bet after round
}

std::string CoinFlip::getLastResultString() const
{
    return lastResult == 1 ? "HEADS" : "TAILS";
}

// Interface implementations
double CoinFlip::getHouseEdge() const { return 0.025; } // 2.5% house edge
std::string CoinFlip::getGameName() const { return "Coin Flip"; }
bool CoinFlip::isGameActive() const { return gameActive; }

uint64_t CoinFlip::getTotalRoundsPlayed() const { return totalRounds; }
double CoinFlip::getTotalAmountWagered() const { return totalWagered; }
double CoinFlip::getTotalAmountWon() const { return totalWon; }