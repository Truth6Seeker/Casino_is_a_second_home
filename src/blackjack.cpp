#include "blackjack.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "player.h"

Blackjack::Blackjack()
    : dealerScore(0),
      playerScore(0),
      gameActive(false),
      currentBet(0.0),
      roundsPlayed(0),
      totalWagered(0.0),
      totalWon(0.0) {
  srand(static_cast<unsigned>(time(0)));
}

int Blackjack::calculateHandScore(const std::vector<int>& hand) const {
  int score = 0;
  int aceCount = 0;

  for (int card : hand) {
    if (card == 1) {  // Ace
      score += 11;
      aceCount++;
    } else if (card >= 10) {  // Face card
      score += 10;
    } else {
      score += card;
    }
  }

  // Adjust for aces if over 21
  while (score > 21 && aceCount > 0) {
    score -= 10;
    aceCount--;
  }

  return score;
}

std::string Blackjack::cardToString(int card) const {
  switch (card) {
    case 1:
      return "A";
    case 11:
      return "J";
    case 12:
      return "Q";
    case 13:
      return "K";
    default:
      return std::to_string(card);
  }
}

void Blackjack::startGame(std::shared_ptr<Player> player) {
  currentPlayer = player;
  gameActive = true;
}

bool Blackjack::placeBet(double amount) {
  if (!gameActive || !currentPlayer || amount <= 0) return false;

  if (!currentPlayer->withdraw(amount)) return false;

  currentBet = amount;
  totalWagered += amount;
  return true;
}

void Blackjack::playRound() {
  if (!gameActive || currentBet <= 0) return;

  roundsPlayed++;
  dealerScore = 0;
  playerScore = 0;
  playerCards.clear();
  dealerCards.clear();

  dealInitialCards();
  playerTurn();

  if (playerScore <= 21) {
    dealerTurn();
    determineWinner();
  } else {
    std::cout << "Busted! You lose.\n";
  }

  currentBet = 0;
}

void Blackjack::endGame() {
  gameActive = false;
  std::cout << "=== Blackjack Game Ended ===\n";
}

double Blackjack::getHouseEdge() const { return 0.05; }
std::string Blackjack::getGameName() const { return "Blackjack"; }
bool Blackjack::isGameActive() const { return gameActive; }

uint64_t Blackjack::getTotalRoundsPlayed() const { return roundsPlayed; }
double Blackjack::getTotalAmountWagered() const { return totalWagered; }
double Blackjack::getTotalAmountWon() const { return totalWon; }

void Blackjack::payout(double multiplier) {
  double winnings = currentBet * multiplier;
  currentPlayer->deposit(winnings);
  totalWon += winnings;
}

void Blackjack::dealInitialCards() {
  // Deal player cards
  playerCards.push_back(getCardValue());
  playerCards.push_back(getCardValue());
  playerScore = calculateHandScore(playerCards);

  // Deal dealer cards
  dealerCards.push_back(getCardValue());
  dealerCards.push_back(getCardValue());
  dealerScore = calculateHandScore(dealerCards);

  std::cout << "\n--- New Round ---\n";
  std::cout << "Your cards: ";
  for (int card : playerCards) std::cout << cardToString(card) << " ";
  std::cout << "= " << playerScore << "\n";

  std::cout << "Dealer shows: " << cardToString(dealerCards[0]) << " and ?\n";
}

void Blackjack::playerTurn() {
  char choice;
  do {
    std::cout << "\nYour hand: ";
    for (int card : playerCards) std::cout << cardToString(card) << " ";
    std::cout << "= " << playerScore << "\n";

    std::cout << "Hit or Stand? (h/s): ";
    std::cin >> choice;
    choice = std::tolower(choice);

    if (choice == 'h') {
      int newCard = getCardValue();
      playerCards.push_back(newCard);
      playerScore = calculateHandScore(playerCards);
      std::cout << "You drew: " << cardToString(newCard) << "\n";
      std::cout << "New total: " << playerScore << "\n";

      if (playerScore > 21) {
        std::cout << "Busted!\n";
        break;
      }
    }
  } while (choice == 'h' && playerScore <= 21);
}

void Blackjack::dealerTurn() {
  std::cout << "\nDealer's turn...\n";
  std::cout << "Dealer's cards: ";
  for (int card : dealerCards) std::cout << cardToString(card) << " ";
  std::cout << "= " << dealerScore << "\n";

  while (dealerScore < 17) {
    int newCard = getCardValue();
    dealerCards.push_back(newCard);
    dealerScore = calculateHandScore(dealerCards);
    std::cout << "Dealer draws: " << cardToString(newCard)
              << " (Total: " << dealerScore << ")\n";

    if (dealerScore > 21) {
      std::cout << "Dealer busted!\n";
      break;
    }
  }
}

void Blackjack::determineWinner() {
  std::cout << "\n--- Results ---\n";
  std::cout << "Your score: " << playerScore << "\n";
  std::cout << "Dealer's score: " << dealerScore << "\n\n";

  if (playerScore > 21) {
    std::cout << "You busted! You lose.\n";
  } else if (dealerScore > 21) {
    std::cout << "Dealer busted! You win!\n";
    payout(2.0);  // 1:1 payout
  } else if (playerScore == 21 && playerCards.size() == 2) {
    std::cout << "Blackjack! You win 3:2!\n";
    payout(2.5);  // 3:2 payout
  } else if (playerScore > dealerScore) {
    std::cout << "You win!\n";
    payout(2.0);  // 1:1 payout
  } else if (playerScore == dealerScore) {
    std::cout << "Push! It's a tie.\n";
    payout(1.0);  // Return bet
  } else {
    std::cout << "Dealer wins!\n";
  }
}

int Blackjack::getCardValue() {
  return (rand() % 13) + 1;  // Cards 1-13
}