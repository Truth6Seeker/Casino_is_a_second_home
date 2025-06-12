// blackjack.cpp
#include "blackjack.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Blackjack::Blackjack() :
    dealerScore(0),
    playerScore(0),
    gameActive(false),
    currentBet(0.0),
    roundsPlayed(0),
    totalWagered(0.0),
    totalWon(0.0)
{
    srand(time(0));
}

void Blackjack::startGame(std::shared_ptr<Player> player) {
    currentPlayer = player;
    gameActive = true;
    std::cout << "=== Blackjack Game Started ===\n";
    playRound();
}

void Blackjack::playRound() {
    if (!gameActive) return;
    
    roundsPlayed++;
    dealerScore = 0;
    playerScore = 0;
    
    dealInitialCards();
    playerTurn();
    
    if (playerScore <= 21) {
        dealerTurn();
        determineWinner();
    }
    
    gameActive = false;
}

void Blackjack::endGame() {
    std::cout << "=== Blackjack Game Ended ===\n";
}

// Остальные обязательные методы
double Blackjack::getHouseEdge() const { return 0.05; }
std::string Blackjack::getGameName() const { return "Blackjack"; }
bool Blackjack::isGameActive() const { return gameActive; }

uint64_t Blackjack::getTotalRoundsPlayed() const { return roundsPlayed; }
double Blackjack::getTotalAmountWagered() const { return totalWagered; }
double Blackjack::getTotalAmountWon() const { return totalWon; }

// Вспомогательные методы
void Blackjack::dealInitialCards() {
    playerScore += getCardValue();
    playerScore += getCardValue();
    dealerScore += getCardValue();
    
    std::cout << "Your cards: " << playerScore << "\n";
    std::cout << "Dealer shows: " << dealerScore << "\n";
}


void Blackjack::playerTurn() {
    char choice;
    do {
        std::cout << "Хотите взять ещё карту? (y/n): ";
        std::cin >> choice;
        if (choice == 'y') {
            playerScore += getCardValue();
            std::cout << "Ваш счёт: " << playerScore << "\n";
            if (playerScore > 21) {
                std::cout << "Перебор! Вы проиграли.\n";
                break;
            }
        }
    } while (choice == 'y');
}

void Blackjack::dealerTurn() {
    std::cout << "Дилер берёт карты...\n";
    while (dealerScore < 17) {
        dealerScore += getCardValue();
    }
    std::cout << "Счёт дилера: " << dealerScore << "\n";
}

void Blackjack::payout()
{
    {
        double winnings = currentBet * 1.8; // Pays 1.8x the bet
        currentPlayer->deposit(winnings);
        totalWon += winnings;
    }
    currentBet = 0; // Reset bet after round
}

void Blackjack::determineWinner() {
    if (playerScore > 21) {
        std::cout << "Вы проиграли.\n";
    } else if (dealerScore > 21) {
        std::cout << "Дилер перебрал! Вы выиграли.\n";
        payout(); // Пример: выигрыш 50 монет
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
    return (rand() % 10) + 1;  // Карты от 1 до 10
}