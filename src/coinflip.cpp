#include "../headers/coinflip.h"
#include <iostream>
#include <chrono>

CoinFlip::CoinFlip() : 
    gameStarted(false),
    currentBet(0.0),
    betOnHeads(false),
    lastResult(0),
    totalRounds(0),
    totalWagered(0.0),
    totalWon(0.0)
{
    // Initialize random number generator with current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
}

void CoinFlip::startGame(std::shared_ptr<Player> p) {
    player = p;
    gameStarted = true;
    totalRounds = 0;
    totalWagered = 0.0;
    totalWon = 0.0;
}

void CoinFlip::playRound() {
    if (!gameStarted || !player) {
        std::cout << "Game not started or player not set!\n";
        return;
    }

    flipCoin();
    handlePayout();
    totalRounds++;
}

void CoinFlip::endGame() {
    gameStarted = false;
    currentBet = 0.0;
    betOnHeads = false;
    lastResult = 0;
}

bool CoinFlip::placeBet(double amount, bool onHeads) {
    if (!gameStarted || !player) {
        std::cout << "Game not started or player not set!\n";
        return false;
    }

    if (amount <= 0 || amount > player->getBalance()) {
        std::cout << "Invalid bet amount!\n";
        return false;
    }

    currentBet = amount;
    betOnHeads = onHeads;
    totalWagered += amount;
    player->withdraw(amount);
    return true;
}

void CoinFlip::flipCoin() {
    // Generate random number (0 or 1)
    std::uniform_int_distribution<int> dist(0, 1);
    lastResult = dist(rng);
}

void CoinFlip::handlePayout() {
    bool won = (lastResult == 1 && betOnHeads) || (lastResult == 0 && !betOnHeads);
    if (won) {
        double winnings = currentBet * 1.95; // 1.95x payout
        player->deposit(winnings);
        totalWon += winnings;
    }
}

std::string CoinFlip::getLastResultString() const {
    return lastResult == 1 ? "Heads" : "Tails";
}

// Interface implementations
double CoinFlip::getHouseEdge() const { return 0.025; } // 2.5% house edge
std::string CoinFlip::getGameName() const { return "Coin Flip"; }
bool CoinFlip::isGameActive() const { return gameStarted; }

uint64_t CoinFlip::getTotalRoundsPlayed() const {
    return static_cast<uint64_t>(totalRounds);
}

double CoinFlip::getTotalAmountWagered() const {
    return totalWagered;
}

double CoinFlip::getTotalAmountWon() const {
    return totalWon;
} 