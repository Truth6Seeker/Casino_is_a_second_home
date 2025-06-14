#pragma once
#include <ctime>
#include <memory>

#include "player.h"

class IGame;  // Forward declaration

class GameSession {
 private:
  std::shared_ptr<Player> player;
  std::shared_ptr<IGame> currentGame;
  time_t startTime;
  double initialBalance;
  double totalWagered;
  double totalWon;

 public:
  GameSession(std::shared_ptr<Player> player);

  // Game management
  bool startGame(std::shared_ptr<IGame> game);
  void endGame();

  // Betting operations
  bool placeBet(double amount);
  void addWinnings(double amount);

  // Session statistics
  double getSessionDuration() const;  // In minutes
  double getNetResult() const;
  double getTotalWagered() const;
  double getTotalWon() const;

  // Accessors
  std::shared_ptr<Player> getPlayer() const;
  std::shared_ptr<IGame> getCurrentGame() const;
  bool isActive() const;
};