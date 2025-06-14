#pragma once
#include "IGame.h"
#include "Player.h"
#include <random>

class CoinFlip : public IGame
{
private:
    std::shared_ptr<Player> currentPlayer;
    bool gameActive;
    double currentBet;
    bool betOnHeads; // true for heads, false for tails

    // Game statistics
    uint64_t totalRounds;
    double totalWagered;
    double totalWon;
    int lastResult; // 0 = tails, 1 = heads

    // Random number generator
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    CoinFlip();

    // IGame interface implementation
    void startGame(std::shared_ptr<Player> player) override;
    void playRound() override;
    void endGame() override;
    double getHouseEdge() const override;
    std::string getGameName() const override;
    bool isGameActive() const override;

    // Game statistics
    uint64_t getTotalRoundsPlayed() const override;
    double getTotalAmountWagered() const override;
    double getTotalAmountWon() const override;

    // Coin flip specific methods
    bool placeBet(double amount, bool betHeads);
    int flipCoin();
    void payout(bool won);
    int getLastResult() const { return lastResult; }
    std::string getLastResultString() const;
};