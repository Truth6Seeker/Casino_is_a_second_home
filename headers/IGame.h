/**
 * @file igame.h
 * @brief Интерфейс для всех игр в казино
 */

#pragma once
#include <memory>

#include "player.h"

/**
 * @class IGame
 * @brief Абстрактный класс, определяющий интерфейс для всех игр в казино
 * 
 * Этот интерфейс определяет основные методы, которые должны быть реализованы
 * всеми играми в казино. Он обеспечивает единообразный способ взаимодействия
 * с различными играми.
 */
class IGame {
 public:
  virtual ~IGame() = default;

  /**
   * @brief Начинает новую игру
   * @param player Указатель на игрока, который будет участвовать в игре
   */
  virtual void startGame(std::shared_ptr<Player> player) = 0;

  /**
   * @brief Проводит один раунд игры
   * 
   * Метод должен быть реализован для конкретной игры и содержать
   * логику проведения одного раунда.
   */
  virtual void playRound() = 0;

  /**
   * @brief Завершает текущую игру
   * 
   * Метод должен выполнить все необходимые действия по завершению игры,
   * включая обновление статистики и освобождение ресурсов.
   */
  virtual void endGame() = 0;

  /**
   * @brief Возвращает преимущество казино в игре
   * @return Преимущество казино в процентах
   */
  virtual double getHouseEdge() const = 0;

  /**
   * @brief Возвращает название игры
   * @return Строка с названием игры
   */
  virtual std::string getGameName() const = 0;

  /**
   * @brief Проверяет, активна ли игра в данный момент
   * @return true если игра активна, false в противном случае
   */
  virtual bool isGameActive() const = 0;

  /**
   * @brief Возвращает общее количество сыгранных раундов
   * @return Количество раундов
   */
  virtual uint64_t getTotalRoundsPlayed() const = 0;

  /**
   * @brief Возвращает общую сумму ставок
   * @return Сумма всех ставок
   */
  virtual double getTotalAmountWagered() const = 0;

  /**
   * @brief Возвращает общую сумму выигрышей
   * @return Сумма всех выигрышей
   */
  virtual double getTotalAmountWon() const = 0;
};