#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <limits>
#include <memory>
#include <vector>

#include "basicstrategyai.h"
#include "card.h"
#include "deck.h"
#include "igame.h"
#include "player.h"

// Новый enum для результата раунда
enum class RoundResult { LOSS, WIN, DRAW, EXIT };

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
  Deck deck;
  std::vector<Card> playerCards;
  std::vector<Card> dealerCards;
  bool gameActive;
  double currentBet;
  bool useBasicStrategy;
  BasicStrategyAI strategyAI;

  // Статистика
  uint64_t roundsPlayed;
  double totalWagered;
  double totalWon;

  void payout();
  void dealInitialCards();
  void playerTurn();
  void dealerTurn();
  void determineWinner();
  int calculateHandValue(const std::vector<Card>& cards) const;
  bool isSoftHand(const std::vector<Card>& cards) const;
  int getDealerUpCard() const;
  bool canSplit() const;
  bool canDoubleDown() const;
  void handleAIAction(BasicStrategyAI::Action action);
  void displayCards(const std::vector<Card>& cards,
                    bool hideFirst = false) const;
};

#endif