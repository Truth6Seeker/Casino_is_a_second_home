#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>

#include "card.h"

class Deck {
 public:
  Deck(int numDecks = 6);  // Default to 6 decks like in most casinos

  void shuffle();
  Card drawCard();
  int cardsRemaining() const;
  double getTrueCount() const;  // Returns the true count for card counting
  void reset();                 // Resets the deck to initial state

 private:
  std::vector<Card> cards;
  int numDecks;
  int runningCount;  // For card counting
  std::mt19937 rng;  // Random number generator

  void initializeDeck();
  void updateRunningCount(const Card& card);
};

#endif  // DECK_H