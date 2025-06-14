#include "Casino.h"
#include "Igame.h"
#include <algorithm>
#include <iostream>

Casino::Casino(const std::string &casinoName)
    : name(casinoName), houseBalance(0) {}

std::shared_ptr<Player> Casino::registerPlayer(const std::string &name, uint32_t age, double initialDeposit)
{
    auto player = std::make_shared<Player>(name, age, initialDeposit);
    players.push_back(player);
    return player;
}

bool Casino::removePlayer(uint64_t playerId)
{
    auto it = std::remove_if(players.begin(), players.end(),
                             [playerId](const std::shared_ptr<Player> &p)
                             {
                                 return p->getId() == playerId;
                             });

    if (it != players.end())
    {
        players.erase(it, players.end());
        return true;
    }
    return false;
}

std::shared_ptr<Player> Casino::getPlayer(uint64_t playerId) const
{
    for (const auto &player : players)
    {
        if (player->getId() == playerId)
        {
            return player;
        }
    }
    return nullptr;
}

std::shared_ptr<GameSession> Casino::createGameSession(uint64_t playerId)
{
    auto player = getPlayer(playerId);
    if (!player)
        return nullptr;

    auto session = std::make_shared<GameSession>(player);
    activeSessions[session->getPlayer()->getId()] = session;
    return session;
}

bool Casino::endGameSession(uint64_t sessionId)
{
    auto it = activeSessions.find(sessionId);
    if (it != activeSessions.end())
    {
        it->second->endGame();
        activeSessions.erase(it);
        return true;
    }
    return false;
}

void Casino::adjustHouseBalance(double amount)
{
    houseBalance += amount;
}

double Casino::getHouseBalance() const
{
    return houseBalance;
}

void Casino::displayActiveSessions() const
{
    std::cout << "Active Sessions in " << name << ":\n";
    for (const auto &pair : activeSessions)
    {
        auto session = pair.second;
        std::cout << "Player: " << session->getPlayer()->getName()
                  << " | Game: " << (session->getCurrentGame() ? session->getCurrentGame()->getGameName() : "None")
                  << " | Duration: " << session->getSessionDuration() << " mins\n";
    }
}

void Casino::displayAllPlayers() const
{
    std::cout << "Registered Players in " << name << ":\n";
    for (const auto &player : players)
    {
        player->displayInfo();
        std::cout << "-----------------\n";
    }
}