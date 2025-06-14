/**
 * @file basicstrategyai.h
 * @brief Класс, реализующий базовую стратегию для блэкджека
 */

#pragma once
#include <string>
#include <vector>

class Card;

/**
 * @class BasicStrategyAI
 * @brief Класс, реализующий базовую стратегию для блэкджека
 * 
 * Этот класс реализует оптимальную базовую стратегию для игры в блэкджек,
 * которая минимизирует преимущество казино.
 */
class BasicStrategyAI {
 public:
  /**
   * @enum Action
   * @brief Возможные действия в игре
   */
  enum class Action { 
    HIT,       ///< Взять карту
    STAND,     ///< Остановиться
    DOUBLE,    ///< Удвоить ставку
    SPLIT,     ///< Разделить пару
    SURRENDER  ///< Сдаться
  };

  /**
   * @brief Конструктор ИИ базовой стратегии
   */
  BasicStrategyAI();

  /**
   * @brief Получить оптимальное действие
   * @param playerScore Счет игрока
   * @param dealerUpCard Открытая карта дилера
   * @param isSoftHand Является ли рука мягкой
   * @param canSplit Можно ли разделить пару
   * @return Оптимальное действие
   */
  Action getAction(int playerScore, int dealerUpCard, bool isSoftHand,
                   bool canSplit) const;

  /**
   * @brief Принять решение на основе карт
   * @param playerCards Карты игрока
   * @param dealerUpCard Открытая карта дилера
   * @return Оптимальное действие
   */
  Action decideAction(const std::vector<Card>& playerCards, const Card& dealerUpCard);

  /**
   * @brief Проверить, является ли рука мягкой
   * @param cards Карты в руке
   * @return true если рука мягкая, false в противном случае
   */
  bool isSoftHand(const std::vector<int>& cards) const;

  /**
   * @brief Проверить возможность удвоения
   * @param playerScore Счет игрока
   * @return true если удвоение возможно, false в противном случае
   */
  bool canDoubleDown(int playerScore) const;

  /**
   * @brief Проверить, стоит ли брать страховку
   * @return true если стоит брать страховку, false в противном случае
   */
  bool shouldTakeInsurance() const;

  /**
   * @brief Проверить, стоит ли брать страховку
   * @param playerCards Карты игрока
   * @param dealerUpCard Открытая карта дилера
   * @return true если стоит брать страховку, false в противном случае
   */
  bool shouldTakeInsurance(const std::vector<Card>& playerCards, const Card& dealerUpCard);

  /**
   * @brief Рассчитать стоимость руки
   * @param cards Карты в руке
   * @return Стоимость руки
   */
  static int calculateHandValue(const std::vector<Card>& cards);

  /**
   * @brief Проверить наличие туза
   * @param cards Карты в руке
   * @return true если есть туз, false в противном случае
   */
  static bool hasAce(const std::vector<Card>& cards);

 private:
  /**
   * @brief Получить действие для жесткой руки
   * @param playerScore Счет игрока
   * @param dealerUpCard Открытая карта дилера
   * @return Оптимальное действие
   */
  Action getHardHandAction(int playerScore, int dealerUpCard) const;

  /**
   * @brief Получить действие для мягкой руки
   * @param playerScore Счет игрока
   * @param dealerUpCard Открытая карта дилера
   * @return Оптимальное действие
   */
  Action getSoftHandAction(int playerScore, int dealerUpCard) const;

  /**
   * @brief Получить действие для пары
   * @param pairValue Значение пары
   * @param dealerUpCard Открытая карта дилера
   * @return Оптимальное действие
   */
  Action getPairAction(int pairValue, int dealerUpCard) const;

  /**
   * @brief Проверить, является ли карта дилера слабой
   * @param dealerCard Карта дилера
   * @return true если карта слабая, false в противном случае
   */
  bool isDealerCardWeak(int dealerCard) const;

  /**
   * @brief Проверить, является ли карта дилера сильной
   * @param dealerCard Карта дилера
   * @return true если карта сильная, false в противном случае
   */
  bool isDealerCardStrong(int dealerCard) const;

  /**
   * @brief Проверить, является ли карта дилера очень слабой
   * @param dealerCard Карта дилера
   * @return true если карта очень слабая, false в противном случае
   */
  bool isDealerCardVeryWeak(int dealerCard) const;

  /**
   * @brief Проверить, является ли карта дилера очень сильной
   * @param dealerCard Карта дилера
   * @return true если карта очень сильная, false в противном случае
   */
  bool isDealerCardVeryStrong(int dealerCard) const;
};