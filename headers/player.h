/**
 * @file player.h
 * @brief Класс, представляющий игрока в казино
 */

#pragma once
#include <cstdint>
#include <string>

/**
 * @class Player
 * @brief Класс, представляющий игрока в казино
 * 
 * Этот класс хранит информацию об игроке, включая его личные данные,
 * баланс и статус верификации.
 */
class Player {
 private:
  std::string name;    ///< Имя игрока
  uint64_t playerId;   ///< Уникальный идентификатор игрока
  double balance;      ///< Текущий баланс игрока
  uint32_t age;        ///< Возраст игрока
  bool verified;       ///< Статус верификации игрока

 public:
  /**
   * @brief Конструктор игрока
   * @param playerName Имя игрока
   * @param playerAge Возраст игрока
   * @param initialBalance Начальный баланс (по умолчанию 0.0)
   */
  Player(const std::string &playerName, uint32_t playerAge,
         double initialBalance = 0.0);

  /**
   * @brief Получить имя игрока
   * @return Имя игрока
   */
  std::string getName() const;

  /**
   * @brief Получить ID игрока
   * @return Уникальный идентификатор игрока
   */
  uint64_t getId() const;

  /**
   * @brief Получить текущий баланс игрока
   * @return Текущий баланс
   */
  double getBalance() const;

  /**
   * @brief Получить возраст игрока
   * @return Возраст игрока
   */
  uint32_t getAge() const;

  /**
   * @brief Проверить статус верификации игрока
   * @return true если игрок верифицирован, false в противном случае
   */
  bool isVerified() const;

  /**
   * @brief Пополнить баланс игрока
   * @param amount Сумма для пополнения
   */
  void deposit(double amount);

  /**
   * @brief Снять деньги с баланса игрока
   * @param amount Сумма для снятия
   * @return true если операция успешна, false если недостаточно средств
   */
  bool withdraw(double amount);

  /**
   * @brief Верифицировать игрока
   * 
   * Устанавливает статус верификации игрока в true
   */
  void verify();

  /**
   * @brief Отобразить информацию об игроке
   * 
   * Выводит в консоль основную информацию об игроке
   */
  void displayInfo() const;
};