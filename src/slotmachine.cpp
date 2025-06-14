#include "../headers/slotmachine.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

SlotMachine::SlotMachine()
    : gameActive(false),
      currentBet(0),
      totalRounds(0),
      totalWagered(0),
      totalWon(0),
      gen(rd()) {}

void SlotMachine::startGame(std::shared_ptr<Player> player) {
  currentPlayer = player;
  gameActive = true;
  totalRounds = 0;
  totalWagered = 0;
  totalWon = 0;
  currentBet = 0;
}

void SlotMachine::playRound() {
  if (!gameActive) return;

  std::vector<std::vector<std::string>> reels(3, std::vector<std::string>(3));
  std::uniform_int_distribution<size_t> dist(0, symbols.size() - 1);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      reels[i][j] = symbols[dist(gen)];
    }
  }

  std::cout << "\n=== Slot Machine Results ===\n";
  for (int i = 0; i < 3; ++i) {
    std::cout << "| ";
    for (int j = 0; j < 3; ++j) {
      std::cout << reels[i][j] << " | ";
    }
    std::cout << "\n";
  }

  std::vector<std::string> centerRow;
  for (int i = 0; i < 3; ++i) {
    centerRow.push_back(reels[i][1]);
  }

  std::map<std::string, int> symbolCounts;
  for (const std::string& symbol : centerRow) {
    symbolCounts[symbol]++;
  }

  double totalWin = 0;
  for (const auto& [symbol, count] : symbolCounts) {
    if (count >= 2) {
      auto symbolPayouts = payTable.find(symbol);
      if (symbolPayouts != payTable.end()) {
        auto payout = symbolPayouts->second.find(count);
        if (payout != symbolPayouts->second.end()) {
          double win = currentBet * payout->second;
          totalWin += win;
          std::cout << count << "x " << symbol << " pays " << win << "\n";
        }
      }
    }
  }

  if (totalWin > 0) {
    std::cout << "Total win: " << totalWin << "\n";
    currentPlayer->deposit(totalWin);
  } else {
    std::cout << "No win this round.\n";
  }

  currentBet = 0;
  gameActive = false;
}

void SlotMachine::endGame() {
  gameActive = false;
  currentPlayer.reset();
  currentBet = 0;
}

bool SlotMachine::placeBet(double amount) {
  if (!gameActive || amount <= 0 || amount > currentPlayer->getBalance()) {
    return false;
  }

  currentBet = amount;
  currentPlayer->withdraw(amount);
  return true;
}

void SlotMachine::placeAllInBet() {
  if (!gameActive) return;
  currentBet = currentPlayer->getBalance();
  currentPlayer->withdraw(currentBet);
}

void SlotMachine::spin() {
  reels.clear();
  std::uniform_int_distribution<size_t> dist(0, symbols.size() - 1);

  for (int i = 0; i < REEL_COUNT; i++) {
    std::vector<std::string> reel;
    for (int j = 0; j < SYMBOLS_PER_REEL; j++) {
      reel.push_back(symbols[dist(gen)]);
    }
    reels.push_back(reel);
  }
}

double SlotMachine::calculatePayout() const {
  // Get center row symbols
  std::vector<std::string> centerRow;
  for (const auto &reel : reels) {
    centerRow.push_back(reel[1]);  // Middle symbol of each reel
  }

  // Count occurrences of each symbol
  std::map<std::string, int> symbolCounts;
  for (const auto &symbol : centerRow) {
    symbolCounts[symbol]++;
  }

  double maxPayout = 0.0;

  // Check payout for each symbol present
  for (const auto &[symbol, count] : symbolCounts) {
    auto symbolPayouts = payTable.find(symbol);
    if (symbolPayouts != payTable.end()) {
      // Check for exact count match
      auto payout = symbolPayouts->second.find(count);
      if (payout != symbolPayouts->second.end()) {
        if (payout->second > maxPayout) {
          maxPayout = payout->second;
        }
      }

      // Special case: cherries pay for at least X
      if (symbol == "C") {
        // Find highest qualifying payout
        for (auto it = symbolPayouts->second.rbegin();
             it != symbolPayouts->second.rend(); ++it) {
          if (count >= it->first) {
            if (it->second > maxPayout) {
              maxPayout = it->second;
            }
            break;
          }
        }
      }
    }
  }

  return maxPayout;
}

void SlotMachine::displayReels() const {
  std::cout << "\n";
  std::cout << "  ----------------\n";
  for (int row = 0; row < SYMBOLS_PER_REEL; row++) {
    std::cout << " | ";
    for (int reel = 0; reel < REEL_COUNT; reel++) {
      std::cout << reels[reel][row] << " | ";
    }
    if (row == 1) std::cout << " <-- PAYLINE";
    std::cout << "\n";
  }
  std::cout << "  ----------------\n";
}

// Interface implementations
double SlotMachine::getHouseEdge() const { return 0.10; }  // 10% house edge
std::string SlotMachine::getGameName() const { return "Slot Machine"; }
bool SlotMachine::isGameActive() const { return gameActive; }

uint64_t SlotMachine::getTotalRoundsPlayed() const { return totalRounds; }
double SlotMachine::getTotalAmountWagered() const { return totalWagered; }
double SlotMachine::getTotalAmountWon() const { return totalWon; }