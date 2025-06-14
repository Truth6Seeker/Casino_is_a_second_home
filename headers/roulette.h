// roulette.h
#ifndef ROULETTE_H
#define ROULETTE_H

#include "igame.h"
#include "player.h"
#include <memory>
#include <vector>

class Roulette : public IGame {
public:
    Roulette();
    
    // Реализация интерфейса IGame
    void startGame(std::shared_ptr<Player> player) override;
    void playRound() override;
    void endGame() override;
    double getHouseEdge() const override;
    std::string getGameName() const override;
    bool isGameActive() const override;
    
    // Статистика
    uint64_t getTotalRoundsPlayed() const override;
    double getTotalAmountWagered() const override;
    double getTotalAmountWon() const override;

private:
    std::shared_ptr<Player> currentPlayer;
    bool gameActive;
    double currentBet;
    
    // Статистика
    uint64_t roundsPlayed;
    double totalWagered;
    double totalWon;

    // Методы игры
    void placeBet();
    void spinWheel();
    void payout(int winningNumber);
    void displayBoard() const;
    std::vector<int> getWinningNumbers(int number) const;
};

#endif // ROULETTE_H