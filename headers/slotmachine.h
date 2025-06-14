/**
 * @file slotmachine.h
 * @brief Класс, реализующий игровой автомат
 */

#pragma once
#include <map>
#include <random>
#include <string>
#include <vector>

#include "igame.h"
#include "player.h"

/**
 * @class SlotMachine
 * @brief Класс, реализующий игровой автомат
 * 
 * Этот класс реализует классический игровой автомат с тремя барабанами
 * и различными символами, каждый из которых имеет свою выплату.
 */
class SlotMachine : public IGame {
 public:
  /**
   * @brief Конструктор игрового автомата
   */
  SlotMachine();

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
   * @brief Сделать ставку
   * @param amount Сумма ставки
   * @return true если ставка успешно сделана, false в противном случае
   */
  bool placeBet(double amount);

  /**
   * @brief Крутить барабаны
   * 
   * Генерирует случайную комбинацию символов на барабанах
   */
  void spin();

  /**
   * @brief Рассчитать выигрыш
   * @return Сумма выигрыша
   */
  double calculatePayout() const;

  /**
   * @brief Отобразить барабаны
   * 
   * Выводит в консоль текущее состояние барабанов
   */
  void displayReels() const;

  /**
   * @brief Сделать ставку на весь баланс
   * 
   * Ставит весь доступный баланс игрока
   */
  void placeAllInBet();

 private:
  std::shared_ptr<Player> currentPlayer;  ///< Текущий игрок
  bool gameActive;                        ///< Статус игры
  double currentBet;                      ///< Текущая ставка

  // Статистика
  uint64_t totalRounds;  ///< Общее количество раундов
  double totalWagered;   ///< Общая сумма ставок
  double totalWon;       ///< Общая сумма выигрышей

  // Настройка барабанов
  static const int REEL_COUNT = 3;           ///< Количество барабанов
  static const int SYMBOLS_PER_REEL = 3;     ///< Количество символов на барабане
  std::vector<std::vector<std::string>> reels;  ///< Текущее состояние барабанов

  // Определения символов и выплат
  std::vector<std::string> symbols = {"C", "L", "O", "S", "B", "7", "D"};  ///< Доступные символы
  std::map<std::string, std::map<int, double>> payTable = {  ///< Таблица выплат
      {"D", {{3, 100.0}, {2, 10.0}}},        ///< Бриллиант
      {"7", {{3, 50.0}, {2, 5.0}}},          ///< Семерка
      {"B", {{3, 20.0}, {2, 3.0}}},          ///< Колокольчик
      {"S", {{3, 15.0}, {2, 2.0}}},          ///< Звезда
      {"O", {{3, 10.0}}},                    ///< Апельсин
      {"L", {{3, 8.0}}},                     ///< Лимон
      {"C", {{3, 5.0}, {2, 2.0}, {1, 1.0}}}  ///< Вишня
  };

  std::random_device rd;  ///< Источник случайных чисел
  std::mt19937 gen;      ///< Генератор случайных чисел
};