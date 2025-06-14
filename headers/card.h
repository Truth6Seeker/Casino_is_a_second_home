/**
 * @file card.h
 * @brief Класс, представляющий игральную карту
 */

#ifndef CARD_H
#define CARD_H

#include <string>

/**
 * @enum Suit
 * @brief Масти игральных карт
 */
enum class Suit { 
  HEARTS,    ///< Червы
  DIAMONDS,  ///< Бубны
  CLUBS,     ///< Трефы
  SPADES     ///< Пики
};

/**
 * @enum Rank
 * @brief Достоинства игральных карт
 */
enum class Rank {
  ACE = 1,   ///< Туз
  TWO = 2,   ///< Двойка
  THREE = 3, ///< Тройка
  FOUR = 4,  ///< Четверка
  FIVE = 5,  ///< Пятерка
  SIX = 6,   ///< Шестерка
  SEVEN = 7, ///< Семерка
  EIGHT = 8, ///< Восьмерка
  NINE = 9,  ///< Девятка
  TEN = 10,  ///< Десятка
  JACK = 11, ///< Валет
  QUEEN = 12,///< Дама
  KING = 13  ///< Король
};

/**
 * @class Card
 * @brief Класс, представляющий игральную карту
 * 
 * Этот класс представляет игральную карту с мастью и достоинством.
 * Предоставляет методы для получения информации о карте и её
 * строкового представления.
 */
class Card {
 public:
  /**
   * @brief Конструктор карты
   * @param suit Масть карты
   * @param rank Достоинство карты
   */
  Card(Suit suit, Rank rank);

  /**
   * @brief Получить масть карты
   * @return Масть карты
   */
  Suit getSuit() const;

  /**
   * @brief Получить достоинство карты
   * @return Достоинство карты
   */
  Rank getRank() const;

  /**
   * @brief Получить значение карты для игры в блэкджек
   * @return Значение карты (туз может быть 1 или 11)
   */
  int getValue() const;          // Returns the blackjack value of the card

  /**
   * @brief Получить строковое представление карты
   * @return Строка вида "Ace of Spades"
   */
  std::string toString() const;  // Returns a string representation of the card

  /**
   * @brief Получить символьное представление карты
   * @return Строка вида "A♠"
   */
  std::string toSymbol() const;  // Returns a symbol representation (e.g., "A♠")

 private:
  Suit suit;  ///< Масть карты
  Rank rank;  ///< Достоинство карты
};

#endif  // CARD_H