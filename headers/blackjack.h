/**
 * @file blackjack.h
 * @brief Класс, реализующий игру в блэкджек
 */

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <limits>
#include <memory>
#include <vector>

#include "basicstrategyai.h"
#include "card.h"
#include "deck.h"
#include "igame.h"
#include "player.h"

/**
 * @enum RoundResult
 * @brief Результат раунда в блэкджеке
 */
enum class RoundResult { 
  LOSS,  ///< Проигрыш
  WIN,   ///< Выигрыш
  DRAW,  ///< Ничья
  EXIT   ///< Выход из игры
};

/**
 * @class Blackjack
 * @brief Класс, реализующий игру в блэкджек
 * 
 * Этот класс реализует классическую игру в блэкджек с поддержкой
 * базовой стратегии для ИИ и подсчета карт.
 */
class Blackjack : public IGame {
 public:
  /**
   * @brief Конструктор игры в блэкджек
   */
  Blackjack();

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
   * @brief Установить использование ИИ
   * @param useAI true для включения ИИ, false для отключения
   */
  void setUseAI(bool useAI) { useBasicStrategy = useAI; }

  /**
   * @brief Проверить, используется ли ИИ
   * @return true если ИИ включен, false в противном случае
   */
  bool isUsingAI() const { return useBasicStrategy; }

  /**
   * @brief Сделать ставку
   * @return true если ставка успешно сделана, false в противном случае
   */
  bool takeBet();

  /**
   * @brief Провести раунд и получить результат
   * @return Результат раунда
   */
  RoundResult playRoundWithResult();

  /**
   * @brief Определить победителя раунда
   * @return Результат раунда
   */
  RoundResult determineWinnerWithResult();

 private:
  std::shared_ptr<Player> currentPlayer;  ///< Текущий игрок
  Deck deck;                              ///< Колода карт
  std::vector<Card> playerCards;          ///< Карты игрока
  std::vector<Card> dealerCards;          ///< Карты дилера
  bool gameActive;                        ///< Статус игры
  double currentBet;                      ///< Текущая ставка
  bool useBasicStrategy;                  ///< Использование базовой стратегии
  BasicStrategyAI strategyAI;             ///< ИИ для базовой стратегии

  // Статистика
  uint64_t roundsPlayed;  ///< Количество сыгранных раундов
  double totalWagered;    ///< Общая сумма ставок
  double totalWon;        ///< Общая сумма выигрышей

  /**
   * @brief Выплатить выигрыш
   */
  void payout();

  /**
   * @brief Раздать начальные карты
   */
  void dealInitialCards();

  /**
   * @brief Ход игрока
   */
  void playerTurn();

  /**
   * @brief Ход дилера
   */
  void dealerTurn();

  /**
   * @brief Определить победителя
   */
  void determineWinner();

  /**
   * @brief Рассчитать стоимость руки
   * @param cards Карты в руке
   * @return Стоимость руки
   */
  int calculateHandValue(const std::vector<Card>& cards) const;

  /**
   * @brief Проверить, является ли рука мягкой
   * @param cards Карты в руке
   * @return true если рука мягкая, false в противном случае
   */
  bool isSoftHand(const std::vector<Card>& cards) const;

  /**
   * @brief Получить открытую карту дилера
   * @return Значение открытой карты дилера
   */
  int getDealerUpCard() const;

  /**
   * @brief Проверить возможность сплита
   * @return true если сплит возможен, false в противном случае
   */
  bool canSplit() const;

  /**
   * @brief Проверить возможность удвоения
   * @return true если удвоение возможно, false в противном случае
   */
  bool canDoubleDown() const;

  /**
   * @brief Обработать действие ИИ
   * @param action Действие, выбранное ИИ
   */
  void handleAIAction(BasicStrategyAI::Action action);

  /**
   * @brief Отобразить карты
   * @param cards Карты для отображения
   * @param hideFirst Скрыть первую карту (для карт дилера)
   */
  void displayCards(const std::vector<Card>& cards,
                    bool hideFirst = false) const;
};

#endif