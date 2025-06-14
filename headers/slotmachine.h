#pragma once
#include "igame.h"
#include "player.h"
#include <vector>
#include <random>
#include <string>
#include <map>

class SlotMachine : public IGame
{
public:
    SlotMachine();

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

    // Slot machine specific methods
    bool placeBet(double amount);
    void spin();
    double calculatePayout() const;
    void displayReels() const;

    // All-in functionality
    void placeAllInBet();

private:
    std::shared_ptr<Player> currentPlayer;
    bool gameActive;
    double currentBet;

    // Game statistics
    uint64_t totalRounds;
    double totalWagered;
    double totalWon;

    // Reel setup
    static const int REEL_COUNT = 3;
    static const int SYMBOLS_PER_REEL = 3;
    std::vector<std::vector<std::string>> reels;

    // Symbol definitions and payouts
    std::vector<std::string> symbols = {"C", "L", "O", "S", "B", "7", "D"};
    std::map<std::string, std::map<int, double>> payTable = {
        {"D", {{3, 100.0}, {2, 10.0}}},       // Diamond
        {"7", {{3, 50.0}, {2, 5.0}}},         // Seven
        {"B", {{3, 20.0}, {2, 3.0}}},         // Bell
        {"S", {{3, 15.0}, {2, 2.0}}},         // Star
        {"O", {{3, 10.0}}},                   // Orange
        {"L", {{3, 8.0}}},                    // Lemon
        {"C", {{3, 5.0}, {2, 2.0}, {1, 1.0}}} // Cherry
    };

    // Random number generator
    std::random_device rd;
    std::mt19937 gen;
}; 