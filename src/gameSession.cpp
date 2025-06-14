#include "gamesession.h"

#include <ctime>
#include <iostream>

#include "igame.h"

GameSession::GameSession(std::shared_ptr<Player> player)
    : player(player),
      currentGame(nullptr),
      startTime(std::time(nullptr)),
      initialBalance(player->getBalance()),
      totalWagered(0),
      totalWon(0) {}

bool GameSession::startGame(std::shared_ptr<IGame> game) {
  if (currentGame != nullptr) {
    return false;  // Already has an active game
  }

  currentGame = game;
  currentGame->startGame(player);
  return true;
}

void GameSession::endGame() {
  if (currentGame != nullptr) {
    currentGame->endGame();
    currentGame = nullptr;
  }
}

bool GameSession::placeBet(double amount) {
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
  return difftime(std::time(nullptr), startTime) / 60.0;  // Minutes
}

double GameSession::getNetResult() const {
  return (player->getBalance() - initialBalance);
}

double GameSession::getTotalWagered() const { return totalWagered; }
double GameSession::getTotalWon() const { return totalWon; }

std::shared_ptr<Player> GameSession::getPlayer() const { return player; }
std::shared_ptr<IGame> GameSession::getCurrentGame() const {
  return currentGame;
}

bool GameSession::isActive() const {
  return currentGame != nullptr && currentGame->isGameActive();
}