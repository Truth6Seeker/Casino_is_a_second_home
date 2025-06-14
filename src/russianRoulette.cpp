#include "RussianRoulette.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

RussianRoulette::RussianRoulette()
    : gameActive(false), gameOver(true), playerTurn(true),
      playerSurvived(false), riskLevel(1), currentChamber(0),
      playerBet(0), houseMatch(0), safePulls(0), totalPulls(0),
      totalRounds(0), totalWagered(0), totalWon(0),
      gen(std::time(nullptr))
{
    chambers.resize(6, false);
}

void RussianRoulette::startGame(std::shared_ptr<Player> player)
{
    currentPlayer = player;
    gameActive = true;
    resetRoundState();
}

void RussianRoulette::playRound()
{
}

void RussianRoulette::endGame()
{
    gameActive = false;
    currentPlayer.reset();
}

double RussianRoulette::getHouseEdge() const { return 0.17; } // 17% house edge
std::string RussianRoulette::getGameName() const { return "Russian Roulette"; }
bool RussianRoulette::isGameActive() const { return gameActive; }
bool RussianRoulette::isGameOver() const { return gameOver; }
bool RussianRoulette::isPlayerTurn() const { return playerTurn; }
bool RussianRoulette::didPlayerSurvive() const { return playerSurvived; }

uint64_t RussianRoulette::getTotalRoundsPlayed() const { return totalRounds; }
double RussianRoulette::getTotalAmountWagered() const { return totalWagered; }
double RussianRoulette::getTotalAmountWon() const { return totalWon; }

void RussianRoulette::setRiskLevel(int bullets)
{
    if (bullets < 1)
        bullets = 1;
    if (bullets > 5)
        bullets = 5;
    riskLevel = bullets;
}

bool RussianRoulette::placeBet(double amount)
{
    if (!gameActive || !currentPlayer || amount <= 0)
        return false;
    if (!currentPlayer->withdraw(amount))
        return false;

    playerBet = amount;
    houseMatch = amount;
    totalWagered += amount;
    gameOver = false;
    playerTurn = true;

    loadRevolver();
    return true;
}

bool RussianRoulette::pullTrigger()
{
    if (gameOver)
        return false;

    totalPulls++;
    bool bulletFired = chambers[currentChamber];

    if (bulletFired)
    {
        if (playerTurn)
        {
            resolvePlayerDeath();
        }
        else
        {
            resolveDealerDeath();
        }
    }
    else
    {
        safePulls++;
        advanceChamber();
        playerTurn = !playerTurn; // Switch turns
    }
    return true;
}

bool RussianRoulette::makeEscape(double amount)
{
    if (gameOver || !playerTurn || amount < playerBet * 0.5)
        return false;

    if (!currentPlayer->withdraw(amount))
        return false;

    // Return original bet to player
    currentPlayer->deposit(playerBet);

    // Calculate escape winnings (partial pot)
    double escapeWinnings = (playerBet + houseMatch) * 0.5;
    currentPlayer->deposit(escapeWinnings);
    totalWon += escapeWinnings;

    endRound(true);
    return true;
}

void RussianRoulette::resetRoundState()
{
    gameOver = true;
    playerSurvived = false;
    playerBet = 0;
    houseMatch = 0;
    safePulls = 0;
    totalPulls = 0;
    std::fill(chambers.begin(), chambers.end(), false);
}

// Helper methods
void RussianRoulette::loadRevolver()
{
    // Clear chambers
    std::fill(chambers.begin(), chambers.end(), false);

    // Randomly load bullets
    std::vector<int> indices(6);
    for (int i = 0; i < 6; i++)
        indices[i] = i;
    std::shuffle(indices.begin(), indices.end(), gen);

    for (int i = 0; i < riskLevel; i++)
    {
        chambers[indices[i]] = true;
    }

    // Randomize starting position
    std::uniform_int_distribution<int> dist(0, 5);
    currentChamber = dist(gen);
    gameOver = false;
    playerSurvived = false;
    safePulls = 0;
    totalPulls = 0;
    playerTurn = true;
}

void RussianRoulette::advanceChamber()
{
    currentChamber = (currentChamber + 1) % 6;
}

void RussianRoulette::resolvePlayerDeath()
{
    totalRounds++;
    endRound(false);
}

void RussianRoulette::resolveDealerDeath()
{
    double winnings = (playerBet + houseMatch) * getCurrentMultiplier();
    currentPlayer->deposit(winnings);
    totalWon += winnings;
    totalRounds++;
    endRound(true);
}

void RussianRoulette::endRound(bool survived)
{
    playerSurvived = survived;
    gameOver = true;
    playerTurn = true;
}

double RussianRoulette::getCurrentMultiplier() const
{
    // Multiplier progression based on safe pulls
    if (safePulls >= 5)
        return 5.0;
    const double multipliers[] = {1.0, 1.2, 1.5, 2.0, 3.0, 5.0};
    return multipliers[safePulls];
}

int RussianRoulette::getBulletsRemaining() const
{
    int count = 0;
    for (bool chamber : chambers)
    {
        if (chamber)
            count++;
    }
    return count;
}

std::string RussianRoulette::getChamberState() const
{
    std::string state;
    for (int i = 0; i < 6; i++)
    {
        if (i == currentChamber)
        {
            state += "[?] ";
        }
        else
        {
            state += "? ";
        }
    }
    return state;
}

std::string RussianRoulette::getLastResultString() const
{
    if (gameOver)
    {
        return playerSurvived ? "SURVIVED" : "ELIMINATED";
    }
    return "IN PROGRESS";
}