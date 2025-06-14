// blackjack.cpp
#include "blackjack.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Blackjack::Blackjack() : dealerScore(0),
                         playerScore(0),
                         gameActive(false),
                         currentBet(0.0),
                         roundsPlayed(0),
                         totalWagered(0.0),
                         totalWon(0.0)
{
    srand(time(0));
}

void Blackjack::startGame(std::shared_ptr<Player> player)
{
    currentPlayer = player;
    gameActive = true;
    std::cout << "=== Blackjack Game Started ===\n";
    playRound();
}

void Blackjack::playRound()
{
    if (!gameActive)
        return;

    roundsPlayed++;
    dealerScore = 0;
    playerScore = 0;

    dealInitialCards();
    playerTurn();

    if (playerScore <= 21)
    {
        dealerTurn();
        determineWinner();
    }

    gameActive = false;
}

void Blackjack::endGame()
{
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
void Blackjack::dealInitialCards()
{
    playerScore += getCardValue();
    playerScore += getCardValue();
    dealerScore += getCardValue();

    std::cout << "Your cards: " << playerScore << "\n";
    std::cout << "Dealer shows: " << dealerScore << "\n";
}

void Blackjack::playerTurn()
{
    char choice;
    do
    {
        std::cout << "Do you want to take another card? (y/n): ";
        std::cin >> choice;
        if (choice == 'y')
        {
            playerScore += getCardValue();
            std::cout << "your count: " << playerScore << "\n";
            if (playerScore > 21)
            {
                std::cout << "Overflow! You lose.\n";
                break;
            }
        }
    } while (choice == 'y');
}

void Blackjack::dealerTurn()
{
    std::cout << "The Dealer pulls a new card...\n";
    while (dealerScore < 17)
    {
        dealerScore += getCardValue();
    }
    std::cout << "Dealer's count: " << dealerScore << "\n";
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

void Blackjack::determineWinner()
{
    if (playerScore > 21)
    {
        std::cout << "You lost.\n";
    }
    else if (dealerScore > 21)
    {
        std::cout << "The Dealer was greedy! You won!.\n";
        payout(); // Пример: выигрыш 50 монет
    }
    else if (playerScore > dealerScore)
    {
        std::cout << "You won!\n";
        payout();
    }
    else if (playerScore == dealerScore)
    {
        std::cout << "It is a draw!\n";
    }
    else
    {
        std::cout << "The dealer won!.\n";
    }
}

int Blackjack::getCardValue()
{
    return (rand() % 10) + 1; // Карты от 1 до 10
}