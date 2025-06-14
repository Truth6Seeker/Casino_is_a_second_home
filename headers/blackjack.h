#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <memory>
#include <string>
#include <vector>

#include "igame.h"
#include "player.h"

class Blackjack : public IGame {
 public:
  Blackjack();

  // IGame interface implementation
  void startGame(std::shared_ptr<Player> player) override;
  void playRound() override;
  void endGame() override;
  double getHouseEdge() const override;
  std::string getGameName() const override;
  bool isGameActive() const override;

  // Statistics
  uint64_t getTotalRoundsPlayed() const override;
  double getTotalAmountWagered() const override;
  double getTotalAmountWon() const override;

  // Blackjack specific
  bool placeBet(double amount);

 private:
  std::shared_ptr<Player> currentPlayer;
  int dealerScore;
  int playerScore;
  bool gameActive;
  double currentBet;

  // Statistics
  uint64_t roundsPlayed;
  double totalWagered;
  double totalWon;

  // Card storage
  std::vector<int> playerCards;
  std::vector<int> dealerCards;

  void payout(double multiplier);
  void dealInitialCards();
  void playerTurn();
  void dealerTurn();
  void determineWinner();
  int getCardValue();
  int calculateHandScore(const std::vector<int>& hand) const;
  std::string cardToString(int card) const;
};

#endif