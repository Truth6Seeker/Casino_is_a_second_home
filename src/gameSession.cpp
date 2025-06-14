#include "../headers/gameSession.h"

#include <ctime>
#include <iostream>

#include "igame.h"

GameSession::GameSession(std::shared_ptr<Player> player)
    : player(player),
      currentGame(nullptr),
      startTime(0),
      initialBalance(player->getBalance()),
      totalWagered(0),
      totalWon(0) {}

bool GameSession::startGame(std::shared_ptr<IGame> game) {
  if (currentGame != nullptr) {
    return false;
  }
  currentGame = game;
  startTime = std::time(nullptr);
  return true;
}

void GameSession::endGame() {
  currentGame = nullptr;
  startTime = 0;
}

bool GameSession::placeBet(double amount) {
  if (currentGame == nullptr || amount <= 0) {
    return false;
  }
  if (player->withdraw(amount)) {
    totalWagered += amount;
    return true;
  }
  return false;
}

void GameSession::addWinnings(double amount) {
  if (amount > 0) {
    player->deposit(amount);
    totalWon += amount;
  }
}

double GameSession::getSessionDuration() const {
  if (startTime == 0) {
    return 0;
  }
  return std::difftime(std::time(nullptr), startTime) / 60.0;
}

double GameSession::getNetResult() const {
  return totalWon - totalWagered;
}

double GameSession::getTotalWagered() const {
  return totalWagered;
}

double GameSession::getTotalWon() const {
  return totalWon;
}

std::shared_ptr<Player> GameSession::getPlayer() const {
  return player;
}

std::shared_ptr<IGame> GameSession::getCurrentGame() const {
  return currentGame;
}

bool GameSession::isActive() const {
  return currentGame != nullptr;
}