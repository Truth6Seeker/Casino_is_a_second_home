#pragma once
#include <memory>
#include "Player.h"

class IGame
{
public:
    virtual ~IGame() = default;

    virtual void startGame(std::shared_ptr<Player> player) = 0;
    virtual void playRound() = 0;
    virtual void endGame() = 0;
    virtual double getHouseEdge() const = 0;
    virtual std::string getGameName() const = 0;
    virtual bool isGameActive() const = 0;

    // Game statistics
    virtual uint64_t getTotalRoundsPlayed() const = 0;
    virtual double getTotalAmountWagered() const = 0;
    virtual double getTotalAmountWon() const = 0;
};