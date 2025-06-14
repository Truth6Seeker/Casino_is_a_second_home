/**
 * @file casino.h
 * @brief Класс, представляющий казино
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "gamesession.h"
#include "player.h"

/**
 * @class Casino
 * @brief Класс, представляющий казино
 * 
 * Этот класс управляет всеми аспектами работы казино, включая
 * регистрацию игроков, управление игровыми сессиями и финансовые операции.
 */
class Casino {
 private:
  std::string name;  ///< Название казино
  std::vector<std::shared_ptr<Player>> players;  ///< Список всех игроков
  std::unordered_map<uint64_t, std::shared_ptr<GameSession>> activeSessions;  ///< Активные игровые сессии
  double houseBalance;  ///< Баланс казино

 public:
  /**
   * @brief Конструктор казино
   * @param casinoName Название казино
   */
  Casino(const std::string &casinoName);

  /**
   * @brief Зарегистрировать нового игрока
   * @param name Имя игрока
   * @param age Возраст игрока
   * @param initialDeposit Начальный депозит (по умолчанию 0.0)
   * @return Указатель на созданного игрока
   */
  std::shared_ptr<Player> registerPlayer(const std::string &name, uint32_t age,
                                         double initialDeposit = 0.0);

  /**
   * @brief Удалить игрока
   * @param playerId ID игрока
   * @return true если игрок успешно удален, false в противном случае
   */
  bool removePlayer(uint64_t playerId);

  /**
   * @brief Получить игрока по ID
   * @param playerId ID игрока
   * @return Указатель на игрока или nullptr, если игрок не найден
   */
  std::shared_ptr<Player> getPlayer(uint64_t playerId) const;

  /**
   * @brief Создать новую игровую сессию
   * @param playerId ID игрока
   * @return Указатель на созданную сессию или nullptr в случае ошибки
   */
  std::shared_ptr<GameSession> createGameSession(uint64_t playerId);

  /**
   * @brief Завершить игровую сессию
   * @param sessionId ID сессии
   * @return true если сессия успешно завершена, false в противном случае
   */
  bool endGameSession(uint64_t sessionId);

  /**
   * @brief Изменить баланс казино
   * @param amount Сумма изменения (положительная для увеличения, отрицательная для уменьшения)
   */
  void adjustHouseBalance(double amount);

  /**
   * @brief Получить текущий баланс казино
   * @return Текущий баланс казино
   */
  double getHouseBalance() const;

  /**
   * @brief Получить название казино
   * @return Название казино
   */
  std::string getName() const { return name; }

  /**
   * @brief Отобразить информацию об активных сессиях
   * 
   * Выводит в консоль информацию о всех активных игровых сессиях
   */
  void displayActiveSessions() const;

  /**
   * @brief Отобразить информацию о всех игроках
   * 
   * Выводит в консоль информацию о всех зарегистрированных игроках
   */
  void displayAllPlayers() const;
};