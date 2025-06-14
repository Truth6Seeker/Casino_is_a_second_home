#include "../headers/player.h"

#include <ctime>
#include <iostream>
#include <random>

Player::Player(const std::string& playerName, uint32_t playerAge,
               double initialBalance)
    : name(playerName), age(playerAge), balance(initialBalance), verified(false) {
  std::mt19937_64 rng(std::time(nullptr));
  playerId = rng();
}

void Player::deposit(double amount) {
  if (amount > 0) {
    balance += amount;
  }
}

bool Player::withdraw(double amount) {
  if (amount > 0 && amount <= balance) {
    balance -= amount;
    return true;
  }
  return false;
}

void Player::verify() { verified = true; }

bool Player::isVerified() const { return verified; }

std::string Player::getName() const { return name; }

uint32_t Player::getAge() const { return age; }

double Player::getBalance() const { return balance; }

uint64_t Player::getId() const { return playerId; }

void Player::displayInfo() const {
  std::cout << "Player ID: " << playerId << "\n"
            << "Name: " << name << "\n"
            << "Age: " << age << "\n"
            << "Balance: $" << balance << "\n"
            << "Verified: " << (verified ? "Yes" : "No") << "\n";
}