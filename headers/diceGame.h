#pragma once
#include "IGame.h"
#include "Player.h"
#include <random>

class DiceGame : public IGame
{
private:
    std::shared_ptr<Player> currentPlayer;
    bool gameActive;
    double currentBet;
    bool betOnHigh; // true for high (4-6), false for low (1-3)

    // Game statistics
    uint64_t totalRounds;
    double totalWagered;
    double totalWon;
    int lastRoll; // Add this to store the last roll result

    // Random number generator
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    DiceGame();

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
    int getLastRoll() const { return lastRoll; }

    // Dice game specific methods
    bool placeBet(double amount, bool betHigh);
    int rollDice();
    void payout(bool won);
};