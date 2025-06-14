// blackjack.cpp
#include "blackjack.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

#include "player.h"

Blackjack::Blackjack()
    : dealerScore(0),
      playerScore(0),
      gameActive(false),
      currentBet(0.0),
      useBasicStrategy(false),
      roundsPlayed(0),
      totalWagered(0.0),
      totalWon(0.0) {
  srand(time(0));
}

void Blackjack::startGame(std::shared_ptr<Player> player) {
  currentPlayer = player;
  gameActive = true;
  std::cout << "=== Blackjack Game Started ===\n";
  // playRound(); // Удалено, чтобы не было двойного раунда
}

void Blackjack::playRound() {
  if (!gameActive) return;

  roundsPlayed++;
  dealerScore = 0;
  playerScore = 0;
  playerCards.clear();

  dealInitialCards();
  playerTurn();

  if (playerScore <= 21) {
    dealerTurn();
    determineWinner();
  }

  gameActive = false;
}

void Blackjack::endGame() { std::cout << "=== Blackjack Game Ended ===\n"; }

// Остальные обязательные методы
double Blackjack::getHouseEdge() const { return 0.05; }
std::string Blackjack::getGameName() const { return "Blackjack"; }
bool Blackjack::isGameActive() const { return gameActive; }

uint64_t Blackjack::getTotalRoundsPlayed() const { return roundsPlayed; }
double Blackjack::getTotalAmountWagered() const { return totalWagered; }
double Blackjack::getTotalAmountWon() const { return totalWon; }

// Вспомогательные методы
void Blackjack::dealInitialCards() {
  int card1 = getCardValue();
  int card2 = getCardValue();
  playerCards.push_back(card1);
  playerCards.push_back(card2);
  playerScore = card1 + card2;
  
  dealerScore = getCardValue();

  std::cout << "Your cards: " << card1 << " and " << card2 << " (Total: " << playerScore << ")\n";
  std::cout << "Dealer shows: " << dealerScore << "\n";
}

void Blackjack::playerTurn() {
  if (useBasicStrategy) {
    // AI's turn
    while (playerScore <= 21) {
      bool isSoft = false;
      for (int card : playerCards) {
        if (card == 11) {
          isSoft = true;
          break;
        }
      }

      BasicStrategyAI::Action action = strategyAI.getAction(
          playerScore, dealerScore, isSoft, canSplit());

      if (action == BasicStrategyAI::Action::STAND) {
        std::cout << "AI decides to stand\n";
        break;
      }

      handleAIAction(action);
      
      if (playerScore > 21) {
        std::cout << "AI busts with " << playerScore << "!\n";
        break;
      }
    }
  } else {
    // Human player's turn
    char choice;
    do {
      std::cout << "Хотите взять ещё карту? (y/n): ";
      std::cin >> choice;
      if (choice == 'y') {
        int newCard = getCardValue();
        playerCards.push_back(newCard);
        playerScore += newCard;
        std::cout << "Новая карта: " << newCard << " (Всего: " << playerScore << ")\n";
        if (playerScore > 21) {
          std::cout << "Перебор! Вы проиграли.\n";
          break;
        }
      }
    } while (choice == 'y');
  }
}

void Blackjack::handleAIAction(BasicStrategyAI::Action action) {
  switch (action) {
    case BasicStrategyAI::Action::HIT: {
      int newCard = getCardValue();
      playerCards.push_back(newCard);
      playerScore += newCard;
      std::cout << "AI hits and gets " << newCard << " (Total: " << playerScore << ")\n";
      break;
    }
    case BasicStrategyAI::Action::DOUBLE: {
      if (canDoubleDown()) {
        int newCard = getCardValue();
        playerCards.push_back(newCard);
        playerScore += newCard;
        currentBet *= 2;
        std::cout << "AI doubles down and gets " << newCard << " (Total: " << playerScore << ")\n";
      } else {
        // If can't double, hit instead
        int newCard = getCardValue();
        playerCards.push_back(newCard);
        playerScore += newCard;
        std::cout << "AI hits and gets " << newCard << " (Total: " << playerScore << ")\n";
      }
      break;
    }
    case BasicStrategyAI::Action::SPLIT: {
      // For simplicity, we'll just hit instead of implementing full split logic
      std::cout << "AI would split, but hitting instead\n";
      int newCard = getCardValue();
      playerCards.push_back(newCard);
      playerScore += newCard;
      std::cout << "AI hits and gets " << newCard << " (Total: " << playerScore << ")\n";
      break;
    }
    case BasicStrategyAI::Action::SURRENDER: {
      // For simplicity, we'll just stand instead of implementing surrender
      std::cout << "AI would surrender, but standing instead\n";
      break;
    }
    default:
      break;
  }
}

bool Blackjack::canSplit() const {
  return playerCards.size() == 2 && playerCards[0] == playerCards[1];
}

bool Blackjack::canDoubleDown() const {
  return playerCards.size() == 2 && playerScore >= 9 && playerScore <= 11;
}

int Blackjack::getPlayerScore() const {
  return playerScore;
}

int Blackjack::getDealerUpCard() const {
  return dealerScore;
}

void Blackjack::dealerTurn() {
  std::cout << "Дилер берёт карты...\n";
  while (dealerScore < 17) {
    dealerScore += getCardValue();
  }
  std::cout << "Счёт дилера: " << dealerScore << "\n";
}

void Blackjack::payout() {
  double winnings = currentBet * 1.8;  // Pays 1.8x the bet
  currentPlayer->deposit(winnings);
  totalWon += winnings;
  currentBet = 0;  // Reset bet after round
}

void Blackjack::determineWinner() {
  if (playerScore > 21) {
    std::cout << "Вы проиграли.\n";
  } else if (dealerScore > 21) {
    std::cout << "Дилер перебрал! Вы выиграли.\n";
    payout();
  } else if (playerScore > dealerScore) {
    std::cout << "Вы выиграли!\n";
    payout();
  } else if (playerScore == dealerScore) {
    std::cout << "Ничья!\n";
  } else {
    std::cout << "Дилер выиграл.\n";
  }
}

int Blackjack::getCardValue() {
  return (rand() % 10) + 1;  // Карты от 2 до 10
}

// Добавим метод для запроса ставки
bool Blackjack::takeBet() {
    double balance = currentPlayer->getBalance();
    double betAmount;
    while (true) {
        std::cout << "Enter bet amount (0 to quit): $";
        if (std::cin >> betAmount) {
            if (betAmount == 0) {
                std::cout << "Thanks for playing!\n";
                gameActive = false;
                return false;
            }
            if (betAmount > 0 && betAmount <= balance) {
                break;
            }
        }
        std::cout << "Invalid amount! Please enter a value between 0 and " << balance << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    currentBet = betAmount;
    currentPlayer->withdraw(currentBet);
    totalWagered += currentBet;
    return true;
}

// Изменим playRound, чтобы возвращать результат
RoundResult Blackjack::playRoundWithResult() {
    if (!gameActive) return RoundResult::LOSS;

    roundsPlayed++;
    dealerScore = 0;
    playerScore = 0;
    playerCards.clear();

    if (!takeBet()) return RoundResult::EXIT;

    dealInitialCards();
    playerTurn();

    if (playerScore > 21) {
        std::cout << "Вы проиграли.\n";
        currentBet = 0;
        gameActive = false;
        return RoundResult::LOSS;
    }

    dealerTurn();
    RoundResult result = determineWinnerWithResult();
    gameActive = false;
    return result;
}

// Новый метод для определения результата и выплат
RoundResult Blackjack::determineWinnerWithResult() {
    if (dealerScore > 21) {
        std::cout << "Дилер перебрал! Вы выиграли.\n";
        currentPlayer->deposit(currentBet * 2);
        totalWon += currentBet * 2;
        currentBet = 0;
        return RoundResult::WIN;
    } else if (playerScore > dealerScore) {
        std::cout << "Вы выиграли!\n";
        currentPlayer->deposit(currentBet * 2);
        totalWon += currentBet * 2;
        currentBet = 0;
        return RoundResult::WIN;
    } else if (playerScore == dealerScore) {
        std::cout << "Ничья! Ставка возвращена.\n";
        currentPlayer->deposit(currentBet);
        currentBet = 0;
        return RoundResult::DRAW;
    } else {
        std::cout << "Дилер выиграл.\n";
        currentBet = 0;
        return RoundResult::LOSS;
    }
}