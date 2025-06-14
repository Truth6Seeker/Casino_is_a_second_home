/**
 * @file gamesession.h
 * @brief Класс, представляющий игровую сессию
 */

#pragma once
#include <ctime>
#include <memory>

#include "player.h"

class IGame;  // Forward declaration

/**
 * @class GameSession
 * @brief Класс, представляющий игровую сессию
 * 
 * Этот класс отслеживает игровую сессию игрока, включая текущую игру,
 * статистику ставок и выигрышей, а также продолжительность сессии.
 */
class GameSession {
 private:
  std::shared_ptr<Player> player;     ///< Указатель на игрока
  std::shared_ptr<IGame> currentGame; ///< Указатель на текущую игру
  time_t startTime;                   ///< Время начала сессии
  double initialBalance;              ///< Начальный баланс игрока
  double totalWagered;                ///< Общая сумма ставок
  double totalWon;                    ///< Общая сумма выигрышей

 public:
  /**
   * @brief Конструктор игровой сессии
   * @param player Указатель на игрока
   */
  GameSession(std::shared_ptr<Player> player);

  /**
   * @brief Начать новую игру
   * @param game Указатель на игру
   * @return true если игра успешно начата, false в противном случае
   */
  bool startGame(std::shared_ptr<IGame> game);

  /**
   * @brief Завершить текущую игру
   * 
   * Завершает текущую игру и обновляет статистику сессии
   */
  void endGame();

  /**
   * @brief Сделать ставку
   * @param amount Сумма ставки
   * @return true если ставка успешно сделана, false в противном случае
   */
  bool placeBet(double amount);

  /**
   * @brief Добавить выигрыш
   * @param amount Сумма выигрыша
   */
  void addWinnings(double amount);

  /**
   * @brief Получить продолжительность сессии
   * @return Продолжительность сессии в минутах
   */
  double getSessionDuration() const;

  /**
   * @brief Получить чистый результат сессии
   * @return Разница между выигрышами и ставками
   */
  double getNetResult() const;

  /**
   * @brief Получить общую сумму ставок
   * @return Общая сумма ставок за сессию
   */
  double getTotalWagered() const;

  /**
   * @brief Получить общую сумму выигрышей
   * @return Общая сумма выигрышей за сессию
   */
  double getTotalWon() const;

  /**
   * @brief Получить указатель на игрока
   * @return Указатель на игрока
   */
  std::shared_ptr<Player> getPlayer() const;

  /**
   * @brief Получить указатель на текущую игру
   * @return Указатель на текущую игру
   */
  std::shared_ptr<IGame> getCurrentGame() const;

  /**
   * @brief Проверить, активна ли сессия
   * @return true если сессия активна, false в противном случае
   */
  bool isActive() const;
};