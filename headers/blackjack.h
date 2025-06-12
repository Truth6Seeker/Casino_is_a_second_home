#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "igame.h"
#include "player.h"
#include <memory>

class Blackjack : public IGame {
public:
    Blackjack();  // Конструктор без параметров
    
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
    int dealerScore;
    int playerScore;
    bool gameActive;
    double currentBet;
    
    // Статистика
    uint64_t roundsPlayed;
    double totalWagered;
    double totalWon;

    void payout();
    void dealInitialCards();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
    int getCardValue();
};

#endif