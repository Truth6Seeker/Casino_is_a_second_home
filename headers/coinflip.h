#pragma once
#include "igame.h"
#include "player.h"
#include <random>

class CoinFlip : public IGame
{
private:
    std::shared_ptr<Player> player;
    bool gameStarted;
    double currentBet;
    bool betOnHeads; // true for heads, false for tails
    int lastResult; // 1 for heads, 0 for tails

    // Game statistics
    int totalRounds;
    double totalWagered;
    double totalWon;

    // Random number generator
    std::mt19937 rng;

public:
    CoinFlip();

    // IGame interface implementation
    void startGame(std::shared_ptr<Player> p) override;
    void playRound() override;
    void endGame() override;
    double getHouseEdge() const override;
    std::string getGameName() const override;
    bool isGameActive() const override;

    // Game statistics
    int getTotalRounds() const { return totalRounds; }
    double getTotalWagered() const { return totalWagered; }
    double getTotalWon() const { return totalWon; }

    // Coin flip specific methods
    bool placeBet(double amount, bool onHeads);
    void flipCoin();
    void handlePayout();
    std::string getLastResultString() const;
    int getLastResult() const { return lastResult; }

    // Реализация чисто виртуальных методов IGame
    uint64_t getTotalRoundsPlayed() const override;
    double getTotalAmountWagered() const override;
    double getTotalAmountWon() const override;
}; 