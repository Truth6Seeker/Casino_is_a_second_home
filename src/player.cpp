#include "Player.h"
#include <iostream>
#include <random>
#include <ctime>

Player::Player(const std::string &playerName, uint32_t playerAge, double initialBalance)
    : name(playerName), age(playerAge), balance(initialBalance), verified(false)
{
    // Generate a pseudo-random player ID
    std::mt19937_64 rng(std::time(nullptr));
    playerId = rng();
}

std::string Player::getName() const { return name; }
uint64_t Player::getId() const { return playerId; }
double Player::getBalance() const { return balance; }
uint32_t Player::getAge() const { return age; }
bool Player::isVerified() const { return verified; }

void Player::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
}

bool Player::withdraw(double amount)
{
    if (amount > 0 && balance >= amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}

void Player::verify()
{
    verified = true;
}

void Player::displayInfo() const
{
    std::cout << "Player ID: " << playerId << "\n"
              << "Name: " << name << "\n"
              << "Age: " << age << "\n"
              << "Balance: $" << balance << "\n"
              << "Status: " << (verified ? "Verified" : "Not Verified") << "\n";
}