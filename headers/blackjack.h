#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <memory>
#include <vector>
#include <limits>

#include "basicstrategyai.h"
#include "igame.h"
#include "player.h"

// Новый enum для результата раунда
enum class RoundResult {
    LOSS,
    WIN,
    DRAW,
    EXIT
};

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

  // AI control
  void setUseAI(bool useAI) { useBasicStrategy = useAI; }
  bool isUsingAI() const { return useBasicStrategy; }

  // Новые методы для корректного расчёта ставок и результата
  bool takeBet();
  RoundResult playRoundWithResult();
  RoundResult determineWinnerWithResult();

 private:
  std::shared_ptr<Player> currentPlayer;
  int dealerScore;
  int playerScore;
  bool gameActive;
  double currentBet;
  bool useBasicStrategy;
  BasicStrategyAI strategyAI;
  std::vector<int> playerCards;

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
  int getDealerUpCard() const;
  bool canSplit() const;
  bool canDoubleDown() const;
  int getPlayerScore() const;
  void handleAIAction(BasicStrategyAI::Action action);
};

#endif