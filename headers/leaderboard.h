#pragma once
#include <string>
#include <vector>

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

    std::string dbPath = "./leaderboard.db";  // База данных создается в текущей директории
    void* db; // sqlite3*
}; 