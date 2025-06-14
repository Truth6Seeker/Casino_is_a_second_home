#include "leaderboard.h"
#include <sqlite3.h>
#include <iostream>
#include <filesystem>

Leaderboard::Leaderboard() : db(nullptr) {
    openDB();
    createTableIfNotExists();
}

Leaderboard::~Leaderboard() {
    closeDB();
}

void Leaderboard::openDB() {
    std::cout << "[DEBUG] Opening DB at: " << dbPath << std::endl;
    if (sqlite3_open(dbPath.c_str(), (sqlite3**)&db) != SQLITE_OK) {
        std::cerr << "Can't open leaderboard database: " << sqlite3_errmsg((sqlite3*)db) << "\n";
        db = nullptr;
    }
}

void Leaderboard::closeDB() {
    if (db) sqlite3_close((sqlite3*)db);
}

void Leaderboard::createTableIfNotExists() {
    if (!db) return;  // Если база не открыта, выходим

    const char* sql = "CREATE TABLE IF NOT EXISTS leaderboard ("
                      "name TEXT PRIMARY KEY, "
                      "balance REAL, "
                      "games_played INTEGER DEFAULT 0, "
                      "wins INTEGER DEFAULT 0"
                      ");";
    char* errMsg = nullptr;
    sqlite3_exec((sqlite3*)db, sql, nullptr, nullptr, &errMsg);
    if (errMsg) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Leaderboard::addOrUpdatePlayer(const std::string& name, double balance, int wins, int games_played) {
    if (!db) return;  // Если база не открыта, выходим

    // Получить текущие значения
    int old_wins = 0, old_games = 0;
    double old_balance = 0;
    const char* select_sql = "SELECT balance, games_played, wins FROM leaderboard WHERE name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, select_sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        old_balance = sqlite3_column_double(stmt, 0);
        old_games = sqlite3_column_int(stmt, 1);
        old_wins = sqlite3_column_int(stmt, 2);
    }
    sqlite3_finalize(stmt);

    // Сохраняем только лучшие значения
    int final_games = std::max(old_games, games_played);
    int final_wins = std::max(old_wins, wins);
    double final_balance = std::max(old_balance, balance);

    std::cout << "[DEBUG] Save to leaderboard: " << name << " | $" << final_balance << " | Games: " << final_games << " | Wins: " << final_wins << std::endl;

    const char* sql =
        "INSERT INTO leaderboard (name, balance, games_played, wins) VALUES (?, ?, ?, ?) "
        "ON CONFLICT(name) DO UPDATE SET "
        "balance=?, games_played=?, wins=?;";
    sqlite3_prepare_v2((sqlite3*)db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, final_balance);
    sqlite3_bind_int(stmt, 3, final_games);
    sqlite3_bind_int(stmt, 4, final_wins);
    sqlite3_bind_double(stmt, 5, final_balance);
    sqlite3_bind_int(stmt, 6, final_games);
    sqlite3_bind_int(stmt, 7, final_wins);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::vector<LeaderboardEntry> Leaderboard::getTopPlayers(int limit) {
    std::vector<LeaderboardEntry> result;
    if (!db) return result;  // Если база не открыта, возвращаем пустой результат

    const char* sql = "SELECT name, balance, games_played, wins FROM leaderboard ORDER BY balance DESC LIMIT ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, limit);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        LeaderboardEntry entry;
        entry.name = (const char*)sqlite3_column_text(stmt, 0);
        entry.balance = sqlite3_column_double(stmt, 1);
        entry.games_played = sqlite3_column_int(stmt, 2);
        entry.wins = sqlite3_column_int(stmt, 3);
        result.push_back(entry);
    }
    sqlite3_finalize(stmt);
    return result;
} 