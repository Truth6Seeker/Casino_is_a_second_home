#pragma once
#include <string>
#include <vector>
#include <filesystem>

struct LeaderboardEntry {
    std::string name;
    double balance;
    int games_played;
    int wins;
};

class Leaderboard {
public:
    Leaderboard();
    ~Leaderboard();

    void addOrUpdatePlayer(const std::string& name, double balance, int wins, int games_played);
    std::vector<LeaderboardEntry> getTopPlayers(int limit = 10);

private:
    void openDB();
    void closeDB();
    void createTableIfNotExists();

    std::string dbPath;
    void* db; // sqlite3*
}; 