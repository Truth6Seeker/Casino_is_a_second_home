/**
 * @file roulette.h
 * @brief Класс, реализующий игру в рулетку
 */

#ifndef ROULETTE_H
#define ROULETTE_H

#include <memory>
#include <vector>

#include "igame.h"
#include "player.h"

/**
 * @class Roulette
 * @brief Класс, реализующий игру в рулетку
 * 
 * Этот класс реализует классическую европейскую рулетку с одним нулем
 * и всеми стандартными типами ставок.
 */
class Roulette : public IGame {
 public:
  /**
   * @brief Конструктор игры в рулетку
   */
  Roulette();

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

 private:
  std::shared_ptr<Player> currentPlayer;  ///< Текущий игрок
  bool gameActive;                        ///< Статус игры
  double currentBet;                      ///< Текущая ставка

  // Статистика
  uint64_t roundsPlayed;  ///< Количество сыгранных раундов
  double totalWagered;    ///< Общая сумма ставок
  double totalWon;        ///< Общая сумма выигрышей

  /**
   * @brief Сделать ставку
   * 
   * Запрашивает у игрока тип и сумму ставки
   */
  void placeBet();

  /**
   * @brief Крутить рулетку
   * 
   * Генерирует случайное число и определяет выигрышные ставки
   */
  void spinWheel();

  /**
   * @brief Выплатить выигрыш
   * @param winningNumber Выпавшее число
   */
  void payout(int winningNumber);

  /**
   * @brief Отобразить игровое поле
   * 
   * Выводит в консоль текущее состояние игрового поля
   */
  void displayBoard() const;

  /**
   * @brief Получить выигрышные числа
   * @param number Выпавшее число
   * @return Вектор выигрышных чисел для данного результата
   */
  std::vector<int> getWinningNumbers(int number) const;
};

#endif  // ROULETTE_H