#include "deck.h"
#include <algorithm>
#include <chrono>

Deck::Deck(int numDecks) : numDecks(numDecks), runningCount(0) {
    // Initialize random number generator with current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    
    initializeDeck();
    shuffle();
}

void Deck::initializeDeck() {
    cards.clear();
    runningCount = 0;
    
    // Create multiple decks
    for (int d = 0; d < numDecks; ++d) {
        // Create one deck
        for (int s = 0; s < 4; ++s) {  // For each suit
            for (int r = 1; r <= 13; ++r) {  // For each rank
                cards.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r));
            }
        }
    }
}

void Deck::shuffle() {
    // Fisher-Yates shuffle algorithm
    for (size_t i = cards.size() - 1; i > 0; --i) {
        std::uniform_int_distribution<size_t> dist(0, i);
        size_t j = dist(rng);
        std::swap(cards[i], cards[j]);
    }
    runningCount = 0;  // Reset running count after shuffle
}

Card Deck::drawCard() {
    if (cards.empty()) {
        throw std::runtime_error("No cards left in deck!");
    }
    
    Card card = cards.back();
    cards.pop_back();
    updateRunningCount(card);
    return card;
}

int Deck::cardsRemaining() const {
    return static_cast<int>(cards.size());
}

double Deck::getTrueCount() const {
    if (cards.empty()) return 0.0;
    return static_cast<double>(runningCount) / (cards.size() / 52.0);
}

void Deck::reset() {
    initializeDeck();
    shuffle();
}

void Deck::updateRunningCount(const Card& card) {
    // Hi-Lo counting system
    int value = card.getValue();
    if (value >= 10) {
        runningCount--;  // High cards (10, J, Q, K, A) decrease count
    } else if (value <= 6) {
        runningCount++;  // Low cards (2-6) increase count
    }
    // 7, 8, 9 are neutral
} 