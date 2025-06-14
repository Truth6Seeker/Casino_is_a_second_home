/**
 * @file leaderboard.h
 * @brief Класс, реализующий таблицу лидеров
 */

#pragma once
#include <filesystem>
#include <string>
#include <vector>

/**
 * @struct LeaderboardEntry
 * @brief Структура, представляющая запись в таблице лидеров
 */
struct LeaderboardEntry {
  std::string name;      ///< Имя игрока
  double balance;        ///< Текущий баланс
  int games_played;      ///< Количество сыгранных игр
  int wins;             ///< Количество побед
};

/**
 * @class Leaderboard
 * @brief Класс, реализующий таблицу лидеров
 * 
 * Этот класс управляет таблицей лидеров, хранящей информацию
 * о лучших игроках в базе данных SQLite.
 */
class Leaderboard {
 public:
  /**
   * @brief Конструктор таблицы лидеров
   */
  Leaderboard();

  /**
   * @brief Деструктор таблицы лидеров
   */
  ~Leaderboard();

  /**
   * @brief Добавить или обновить игрока в таблице лидеров
   * @param name Имя игрока
   * @param balance Текущий баланс
   * @param wins Количество побед
   * @param games_played Количество сыгранных игр
   */
  void addOrUpdatePlayer(const std::string& name, double balance, int wins,
                         int games_played);

  /**
   * @brief Получить список лучших игроков
   * @param limit Максимальное количество игроков (по умолчанию 10)
   * @return Вектор записей с лучшими игроками
   */
  std::vector<LeaderboardEntry> getTopPlayers(int limit = 10);

 private:
  /**
   * @brief Открыть соединение с базой данных
   */
  void openDB();

  /**
   * @brief Закрыть соединение с базой данных
   */
  void closeDB();

  /**
   * @brief Создать таблицу, если она не существует
   */
  void createTableIfNotExists();

  std::string dbPath;  ///< Путь к файлу базы данных
  void* db;           ///< Указатель на соединение с базой данных (sqlite3*)
};