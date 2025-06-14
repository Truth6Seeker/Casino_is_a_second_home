#include "../headers/slotmachine.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

SlotMachine::SlotMachine()
    : gameActive(false), currentBet(0), totalRounds(0),
      totalWagered(0), totalWon(0), gen(rd()) {}

void SlotMachine::startGame(std::shared_ptr<Player> player)
{
    currentPlayer = player;
    gameActive = true;
    totalRounds = 0;
    totalWagered = 0;
    totalWon = 0;
    currentBet = 0;
}

void SlotMachine::playRound()
{
    if (!gameActive || currentBet <= 0)
        return;

    spin();
    displayReels();

    double winnings = calculatePayout() * currentBet;
    if (winnings > 0)
    {
        currentPlayer->deposit(winnings);
        totalWon += winnings;
        std::cout << "\nJACKPOT!! You won $" << winnings << "!! (0_0)\n";
    }
    else
    {
        std::cout << "\nNo winning combination. Better luck next time!\n";
    }

    totalRounds++;
    currentBet = 0; // Reset bet after round
}

void SlotMachine::endGame()
{
    gameActive = false;
    currentPlayer.reset();
    currentBet = 0;
}

bool SlotMachine::placeBet(double amount)
{
    if (!gameActive || amount <= 0)
        return false;

    if (!currentPlayer->withdraw(amount))
    {
        return false; // Insufficient funds
    }

    currentBet = amount;
    totalWagered += amount;
    return true;
}

void SlotMachine::placeAllInBet()
{
    if (!gameActive)
        return;

    double balance = currentPlayer->getBalance();
    if (balance <= 0)
        return;

    if (currentPlayer->withdraw(balance))
    {
        currentBet = balance;
        totalWagered += balance;
    }
}

void SlotMachine::spin()
{
    reels.clear();
    std::uniform_int_distribution<size_t> dist(0, symbols.size() - 1);

    for (int i = 0; i < REEL_COUNT; i++)
    {
        std::vector<std::string> reel;
        for (int j = 0; j < SYMBOLS_PER_REEL; j++)
        {
            reel.push_back(symbols[dist(gen)]);
        }
        reels.push_back(reel);
    }
}

double SlotMachine::calculatePayout() const
{
    // Get center row symbols
    std::vector<std::string> centerRow;
    for (const auto &reel : reels)
    {
        centerRow.push_back(reel[1]); // Middle symbol of each reel
    }

    // Count occurrences of each symbol
    std::map<std::string, int> symbolCounts;
    for (const auto &symbol : centerRow)
    {
        symbolCounts[symbol]++;
    }

    double maxPayout = 0.0;

    // Check payout for each symbol present
    for (const auto &[symbol, count] : symbolCounts)
    {
        auto symbolPayouts = payTable.find(symbol);
        if (symbolPayouts != payTable.end())
        {
            // Check for exact count match
            auto payout = symbolPayouts->second.find(count);
            if (payout != symbolPayouts->second.end())
            {
                if (payout->second > maxPayout)
                {
                    maxPayout = payout->second;
                }
            }

            // Special case: cherries pay for at least X
            if (symbol == "C")
            {
                // Find highest qualifying payout
                for (auto it = symbolPayouts->second.rbegin(); it != symbolPayouts->second.rend(); ++it)
                {
                    if (count >= it->first)
                    {
                        if (it->second > maxPayout)
                        {
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

void SlotMachine::displayReels() const
{
    std::cout << "\n";
    std::cout << "  ----------------\n";
    for (int row = 0; row < SYMBOLS_PER_REEL; row++)
    {
        std::cout << " | ";
        for (int reel = 0; reel < REEL_COUNT; reel++)
        {
            std::cout << reels[reel][row] << " | ";
        }
        if (row == 1)
            std::cout << " <-- PAYLINE";
        std::cout << "\n";
    }
    std::cout << "  ----------------\n";
}

// Interface implementations
double SlotMachine::getHouseEdge() const { return 0.10; } // 10% house edge
std::string SlotMachine::getGameName() const { return "Slot Machine"; }
bool SlotMachine::isGameActive() const { return gameActive; }

uint64_t SlotMachine::getTotalRoundsPlayed() const { return totalRounds; }
double SlotMachine::getTotalAmountWagered() const { return totalWagered; }
double SlotMachine::getTotalAmountWon() const { return totalWon; }