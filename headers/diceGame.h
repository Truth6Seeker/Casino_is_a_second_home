/**
 * @file dicegame.h
 * @brief Класс, реализующий игру в кости
 */

#pragma once
#include <random>

#include "igame.h"
#include "player.h"

/**
 * @class DiceGame
 * @brief Класс, реализующий игру в кости
 * 
 * Этот класс реализует простую игру в кости, где игрок может
 * сделать ставку на высокое (4-6) или низкое (1-3) значение.
 */
class DiceGame : public IGame {
 private:
  std::shared_ptr<Player> currentPlayer;  ///< Текущий игрок
  bool gameActive;                        ///< Статус игры
  double currentBet;                      ///< Текущая ставка
  bool betOnHigh;                         ///< Ставка на высокое (true) или низкое (false)

  // Статистика игры
  uint64_t totalRounds;  ///< Общее количество раундов
  double totalWagered;   ///< Общая сумма ставок
  double totalWon;       ///< Общая сумма выигрышей
  int lastRoll;          ///< Результат последнего броска

  // Генератор случайных чисел
  std::random_device rd;  ///< Источник случайных чисел
  std::mt19937 gen;      ///< Генератор случайных чисел
  std::uniform_int_distribution<> dist;  ///< Распределение для броска кости

 public:
  /**
   * @brief Конструктор игры в кости
   */
  DiceGame();

  /**
   * @brief Начать новую игру
   * @param player Указатель на игрока
   */
  void startGame(std::shared_ptr<Player> player) override;

  /**
   * @brief Провести один раунд игры
   */
  void playRound() override;

  /**
   * @brief Завершить игру
   */
  void endGame() override;

  /**
   * @brief Получить преимущество казино
   * @return Преимущество казино в процентах
   */
  double getHouseEdge() const override;

  /**
   * @brief Получить название игры
   * @return Название игры
   */
  std::string getGameName() const override;

  /**
   * @brief Проверить, активна ли игра
   * @return true если игра активна, false в противном случае
   */
  bool isGameActive() const override;

  /**
   * @brief Получить количество сыгранных раундов
   * @return Количество раундов
   */
  uint64_t getTotalRoundsPlayed() const override;

  /**
   * @brief Получить общую сумму ставок
   * @return Сумма всех ставок
   */
  double getTotalAmountWagered() const override;

  /**
   * @brief Получить общую сумму выигрышей
   * @return Сумма всех выигрышей
   */
  double getTotalAmountWon() const override;

  /**
   * @brief Получить результат последнего броска
   * @return Значение последнего броска
   */
  int getLastRoll() const { return lastRoll; }

  /**
   * @brief Сделать ставку
   * @param amount Сумма ставки
   * @param betHigh true для ставки на высокое, false для ставки на низкое
   * @return true если ставка успешно сделана, false в противном случае
   */
  bool placeBet(double amount, bool betHigh);

  /**
   * @brief Бросить кость
   * @return Результат броска (1-6)
   */
  int rollDice();

  /**
   * @brief Выплатить выигрыш
   * @param won true если игрок выиграл, false в противном случае
   */
  void payout(bool won);
};