// roulette.cpp
#include "roulette.h"
#include <iostream>
#include <ctime>
#include <iomanip>

Roulette::Roulette() :
    gameActive(false),
    currentBet(0.0),
    roundsPlayed(0),
    totalWagered(0.0),
    totalWon(0.0)
{
    srand(time(0));
}

void Roulette::startGame(std::shared_ptr<Player> player) {
    currentPlayer = player;
    gameActive = true;
    std::cout << "\n=== Добро пожаловать в Рулетку! ===\n";
    std::cout << "Ставки принимаются на:\n";
    std::cout << "- Числа (1-36), выплата 35:1\n";
    std::cout << "- Чёт/Нечёт, Красное/Чёрное, 1-18/19-36, выплата 1:1\n";
    playRound();
}

void Roulette::playRound() {
    if (!gameActive) return;
    
    displayBoard();
    placeBet();
    spinWheel();
    
    gameActive = false;
}

void Roulette::endGame() {
    std::cout << "=== Игра в рулетку завершена ===\n";
}

double Roulette::getHouseEdge() const { return 0.027; } // 2.7% для европейской рулетки
std::string Roulette::getGameName() const { return "Roulette"; }
bool Roulette::isGameActive() const { return gameActive; }

uint64_t Roulette::getTotalRoundsPlayed() const { return roundsPlayed; }
double Roulette::getTotalAmountWagered() const { return totalWagered; }
double Roulette::getTotalAmountWon() const { return totalWon; }

void Roulette::placeBet() {
    double betAmount;
    std::cout << "\nВаш баланс: $" << currentPlayer->getBalance() << "\n";
    std::cout << "Введите сумму ставки (0 для выхода): $";
    std::cin >> betAmount;
    
    if (betAmount <= 0 || betAmount > currentPlayer->getBalance()) {
        std::cout << "Неверная сумма ставки!\n";
        gameActive = false;
        return;
    }
    
    currentBet = betAmount;
    currentPlayer->withdraw(betAmount);
    totalWagered += betAmount;
    roundsPlayed++;
}

void Roulette::spinWheel() {
    int winningNumber = rand() % 37; // 0-36
    std::cout << "\nШар останавливается на... " << winningNumber << "!\n";
    
    payout(winningNumber);
}

void Roulette::payout(int winningNumber) {
    // Здесь должна быть логика определения выигрыша
    // Для примера - просто возвращаем ставку
    double winnings = currentBet * 2;
    currentPlayer->deposit(winnings);
    totalWon += winnings;
    std::cout << "Вы выиграли $" << winnings << "!\n";
}

void Roulette::displayBoard() const {
    std::cout << "\nТаблица рулетки:\n";
    // Простая ASCII-графика для рулетки
    for (int i = 1; i <= 36; i += 3) {
        std::cout << std::setw(2) << i << " ";
        std::cout << std::setw(2) << (i+1) << " ";
        std::cout << std::setw(2) << (i+2) << "\n";
    }
    std::cout << "0\n";
}