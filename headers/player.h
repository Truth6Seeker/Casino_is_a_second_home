#pragma once
#include <string>
#include <cstdint>

class Player
{
private:
    std::string name;
    uint64_t playerId;
    double balance;
    uint32_t age;
    bool verified;

public:
    Player(const std::string &playerName, uint32_t playerAge, double initialBalance = 0.0);

    // Getters
    std::string getName() const;
    uint64_t getId() const;
    double getBalance() const;
    uint32_t getAge() const;
    bool isVerified() const;

    // Financial operations
    void deposit(double amount);
    bool withdraw(double amount); // Returns false if insufficient funds

    // Verification
    void verify();

    // Display
    void displayInfo() const;
};