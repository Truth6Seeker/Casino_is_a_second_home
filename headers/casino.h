#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "gamesession.h"
#include "player.h"

class Casino {
 private:
  std::string name;
  std::vector<std::shared_ptr<Player>> players;
  std::unordered_map<uint64_t, std::shared_ptr<GameSession>> activeSessions;
  double houseBalance;

 public:
  Casino(const std::string &casinoName);

  // Player management
  std::shared_ptr<Player> registerPlayer(const std::string &name, uint32_t age,
                                         double initialDeposit = 0.0);
  bool removePlayer(uint64_t playerId);
  std::shared_ptr<Player> getPlayer(uint64_t playerId) const;

  // Game session management
  std::shared_ptr<GameSession> createGameSession(uint64_t playerId);
  bool endGameSession(uint64_t sessionId);

  // Financial operations
  void adjustHouseBalance(double amount);
  double getHouseBalance() const;

  // Casino information
  std::string getName() const { return name; }

  // Casino operations
  void displayActiveSessions() const;
  void displayAllPlayers() const;
};