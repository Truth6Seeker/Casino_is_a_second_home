/**
 * @file deck.h
 * @brief Класс, представляющий колоду карт
 */

#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>

#include "card.h"

/**
 * @class Deck
 * @brief Класс, представляющий колоду карт
 * 
 * Этот класс представляет колоду карт, которая может содержать
 * несколько стандартных колод. Поддерживает перемешивание карт,
 * подсчет оставшихся карт и подсчет для карточного счета.
 */
class Deck {
 public:
  /**
   * @brief Конструктор колоды
   * @param numDecks Количество колод (по умолчанию 6, как в большинстве казино)
   */
  Deck(int numDecks = 6);

  /**
   * @brief Перемешать колоду
   * 
   * Перемешивает все карты в колоде случайным образом
   */
  void shuffle();

  /**
   * @brief Взять карту из колоды
   * @return Карта, взятая из колоды
   * @throw std::runtime_error если в колоде не осталось карт
   */
  Card drawCard();

  /**
   * @brief Получить количество оставшихся карт
   * @return Количество карт в колоде
   */
  int cardsRemaining() const;

  /**
   * @brief Получить истинный счет для карточного счета
   * @return Истинный счет (running count / decks remaining)
   */
  double getTrueCount() const;

  /**
   * @brief Сбросить колоду в начальное состояние
   * 
   * Пересоздает колоду с исходным количеством карт и перемешивает её
   */
  void reset();

  /**
   * @brief Получить текущий running count
   * @return Текущий running count для карточного счета
   */
  int getRunningCount() const;

 private:
  std::vector<Card> cards;  ///< Вектор карт в колоде
  int numDecks;            ///< Количество колод
  int runningCount;        ///< Текущий running count для карточного счета
  std::mt19937 rng;        ///< Генератор случайных чисел

  /**
   * @brief Инициализировать колоду
   * 
   * Создает новую колоду с заданным количеством колод
   */
  void initializeDeck();

  /**
   * @brief Обновить running count
   * @param card Карта, для которой нужно обновить счет
   */
  void updateRunningCount(const Card& card);
};

#endif  // DECK_H