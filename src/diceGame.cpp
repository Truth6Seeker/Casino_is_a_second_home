#include "DiceGame.h"

DiceGame::DiceGame()
    : gameActive(false), currentBet(0), betOnHigh(false),
      totalRounds(0), totalWagered(0), totalWon(0),
      gen(rd()), dist(1, 6) {} // Initialize RNG for 1-6

void DiceGame::startGame(std::shared_ptr<Player> player)
{
    currentPlayer = player;
    gameActive = true;
    totalRounds = 0;
    totalWagered = 0;
    totalWon = 0;
}

void DiceGame::playRound()
{
    if (!gameActive || currentBet <= 0)
        return;

    int result = rollDice();
    bool win = (result >= 4 && betOnHigh) || (result <= 3 && !betOnHigh);

    payout(win);
    totalRounds++;
}

void DiceGame::endGame()
{
    gameActive = false;
    currentPlayer.reset();
    currentBet = 0;
}

bool DiceGame::placeBet(double amount, bool betHigh)
{
    if (!gameActive || amount <= 0)
        return false;

    if (!currentPlayer->withdraw(amount))
    {
        return false; // Insufficient funds
    }

    currentBet = amount;
    betOnHigh = betHigh;
    totalWagered += amount;
    return true;
}

int DiceGame::rollDice()
{
    lastRoll = dist(gen); // Store the result
    return lastRoll;
}

void DiceGame::payout(bool won)
{
    if (won)
    {
        double winnings = currentBet * 1.8; // Pays 1.8x the bet
        currentPlayer->deposit(winnings);
        totalWon += winnings;
    }
    currentBet = 0; // Reset bet after round
}

// Interface implementations
double DiceGame::getHouseEdge() const { return 0.1111; } // 11.11% house edge
std::string DiceGame::getGameName() const { return "Dice Roll"; }
bool DiceGame::isGameActive() const { return gameActive; }

uint64_t DiceGame::getTotalRoundsPlayed() const { return totalRounds; }
double DiceGame::getTotalAmountWagered() const { return totalWagered; }
double DiceGame::getTotalAmountWon() const { return totalWon; }