#include "deck.h"

#include <algorithm>
#include <chrono>

Deck::Deck(int numDecks) : rng(std::random_device{}()), numDecks(numDecks), runningCount(0) {
  for (int d = 0; d < numDecks; ++d) {
    for (int s = 0; s < 4; ++s) {
      for (int r = 1; r <= 13; ++r) {
        cards.push_back(Card(static_cast<Suit>(s), static_cast<Rank>(r)));
      }
    }
  }
  shuffle();
}

void Deck::shuffle() {
  std::shuffle(cards.begin(), cards.end(), rng);
  runningCount = 0;
}

Card Deck::drawCard() {
  if (cards.empty()) {
    throw std::runtime_error("Deck is empty");
  }

  Card card = cards.back();
  cards.pop_back();

  // Hi-Lo counting system
  Rank rank = card.getRank();
  if (rank >= Rank::TEN || rank == Rank::ACE) {
    runningCount--;
  } else if (rank <= Rank::SIX) {
    runningCount++;
  }

  return card;
}

int Deck::cardsRemaining() const { return static_cast<int>(cards.size()); }

int Deck::getRunningCount() const { return runningCount; }

double Deck::getTrueCount() const {
  return cards.empty() ? 0.0 : static_cast<double>(runningCount) / (static_cast<double>(cards.size()) / 52.0);
}

void Deck::reset() {
  cards.clear();
  for (int s = 0; s < 4; ++s) {
    for (int r = 1; r <= 13; ++r) {
      cards.push_back(Card(static_cast<Suit>(s), static_cast<Rank>(r)));
    }
  }
  shuffle();
}