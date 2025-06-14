#pragma once
#include "IGame.h"
#include "Player.h"
#include <vector>
#include <random>
#include <string>
#include <ctime>

class RussianRoulette : public IGame
{
public:
    RussianRoulette();

    // IGame interface implementation
    void startGame(std::shared_ptr<Player> player) override;
    void playRound() override;
    void endGame() override;
    double getHouseEdge() const override;
    std::string getGameName() const override;
    bool isGameActive() const override;
    uint64_t getTotalRoundsPlayed() const override;
    double getTotalAmountWagered() const override;
    double getTotalAmountWon() const override;

    // Game-specific methods
    void setRiskLevel(int bullets);
    bool placeBet(double amount);
    bool pullTrigger();
    bool makeEscape(double amount);
    void resetRoundState();

    // State query methods
    bool isGameOver() const;
    bool isPlayerTurn() const;
    bool didPlayerSurvive() const;
    double getCurrentMultiplier() const;
    int getBulletsRemaining() const;
    std::string getChamberState() const;
    std::string getLastResultString() const;

private:
    void loadRevolver();
    void advanceChamber();
    void resolvePlayerDeath();
    void resolveDealerDeath();
    void endRound(bool survived);

    std::shared_ptr<Player> currentPlayer;
    bool gameActive;
    bool gameOver;
    bool playerTurn;
    bool playerSurvived;

    // Revolver state
    int riskLevel;
    int currentChamber;
    std::vector<bool> chambers;

    // Game state
    double playerBet;
    double houseMatch;
    int safePulls;
    int totalPulls;

    // Statistics
    uint64_t totalRounds;
    double totalWagered;
    double totalWon;

    // Random engine
    std::mt19937 gen;
};