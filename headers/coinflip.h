/**
 * @file coinflip.h
 * @brief Класс, реализующий игру в подбрасывание монеты
 */

#pragma once
#include <random>

#include "igame.h"
#include "player.h"

/**
 * @class CoinFlip
 * @brief Класс, реализующий игру в подбрасывание монеты
 * 
 * Этот класс реализует простую игру в подбрасывание монеты,
 * где игрок может сделать ставку на орла или решку.
 */
class CoinFlip : public IGame {
 private:
  std::shared_ptr<Player> player;  ///< Указатель на игрока
  bool gameStarted;                ///< Статус игры
  double currentBet;               ///< Текущая ставка
  bool betOnHeads;                 ///< Ставка на орла (true) или решку (false)
  int lastResult;                  ///< Последний результат (1 - орел, 0 - решка)

  // Статистика игры
  int totalRounds;     ///< Общее количество раундов
  double totalWagered; ///< Общая сумма ставок
  double totalWon;     ///< Общая сумма выигрышей

  std::mt19937 rng;    ///< Генератор случайных чисел

 public:
  /**
   * @brief Конструктор игры в подбрасывание монеты
   */
  CoinFlip();

  /**
   * @brief Начать новую игру
   * @param p Указатель на игрока
   */
  void startGame(std::shared_ptr<Player> p) override;

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
  int getTotalRounds() const { return totalRounds; }

  /**
   * @brief Получить общую сумму ставок
   * @return Сумма всех ставок
   */
  double getTotalWagered() const { return totalWagered; }

  /**
   * @brief Получить общую сумму выигрышей
   * @return Сумма всех выигрышей
   */
  double getTotalWon() const { return totalWon; }

  /**
   * @brief Сделать ставку
   * @param amount Сумма ставки
   * @param onHeads true для ставки на орла, false для ставки на решку
   * @return true если ставка успешно сделана, false в противном случае
   */
  bool placeBet(double amount, bool onHeads);

  /**
   * @brief Подбросить монету
   * 
   * Генерирует случайный результат подбрасывания монеты
   */
  void flipCoin();

  /**
   * @brief Обработать выплату
   * 
   * Рассчитывает и выплачивает выигрыш в зависимости от результата
   */
  void handlePayout();

  /**
   * @brief Получить строковое представление последнего результата
   * @return Строка "Heads" или "Tails"
   */
  std::string getLastResultString() const;

  /**
   * @brief Получить последний результат
   * @return 1 для орла, 0 для решки
   */
  int getLastResult() const { return lastResult; }

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
};