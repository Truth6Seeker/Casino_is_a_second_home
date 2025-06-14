// Заимствованный файл(в основном)

#include "leaderboard.h"

#include <sqlite3.h>

#include <filesystem>
#include <iostream>

Leaderboard::Leaderboard() {
  std::filesystem::create_directories("data");
  sqlite3* db;
  int rc = sqlite3_open("data/leaderboard.db", &db);
  if (rc) {
    sqlite3_close(db);
    return;
  }

  const char* sql = "CREATE TABLE IF NOT EXISTS players ("
                    "name TEXT PRIMARY KEY,"
                    "balance REAL,"
                    "games_played INTEGER,"
                    "wins INTEGER);";

  char* errMsg = nullptr;
  rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    sqlite3_free(errMsg);
  }
  sqlite3_close(db);
}

Leaderboard::~Leaderboard() { closeDB(); }

void Leaderboard::openDB() {
  std::cout << "[DEBUG] Opening DB at: " << dbPath << std::endl;
  if (sqlite3_open(dbPath.c_str(), (sqlite3**)&db) != SQLITE_OK) {
    std::cerr << "Can't open leaderboard database: "
              << sqlite3_errmsg((sqlite3*)db) << "\n";
    db = nullptr;
  }
}

void Leaderboard::closeDB() {
  if (db) sqlite3_close((sqlite3*)db);
}

void Leaderboard::createTableIfNotExists() {
  if (!db) return;  // Если база не открыта, выходим

  const char* sql =
      "CREATE TABLE IF NOT EXISTS leaderboard ("
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

void Leaderboard::addOrUpdatePlayer(const std::string& name, double balance,
                                    int wins, int gamesPlayed) {
  sqlite3* db;
  int rc = sqlite3_open("data/leaderboard.db", &db);
  if (!db) return;

  const char* sql = "INSERT OR REPLACE INTO players (name, balance, games_played, wins) "
                    "VALUES (?, ?, ?, ?);";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    sqlite3_close(db);
    return;
  }

  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 2, balance);
  sqlite3_bind_int(stmt, 3, gamesPlayed);
  sqlite3_bind_int(stmt, 4, wins);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

std::vector<LeaderboardEntry> Leaderboard::getTopPlayers(int limit) {
  std::vector<LeaderboardEntry> result;
  sqlite3* db;
  int rc = sqlite3_open("data/leaderboard.db", &db);
  if (!db) return result;

  const char* sql = "SELECT name, balance, games_played, wins FROM players "
                    "ORDER BY balance DESC LIMIT ?;";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    sqlite3_close(db);
    return result;
  }

  sqlite3_bind_int(stmt, 1, limit);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    LeaderboardEntry entry;
    entry.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    entry.balance = sqlite3_column_double(stmt, 1);
    entry.games_played = sqlite3_column_int(stmt, 2);
    entry.wins = sqlite3_column_int(stmt, 3);
    result.push_back(entry);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return result;
}