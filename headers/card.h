#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Rank {
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13
};

class Card {
public:
    Card(Suit suit, Rank rank);
    
    Suit getSuit() const;
    Rank getRank() const;
    int getValue() const;  // Returns the blackjack value of the card
    std::string toString() const;  // Returns a string representation of the card
    std::string toSymbol() const;  // Returns a symbol representation (e.g., "A♠")

private:
    Suit suit;
    Rank rank;
};

#endif // CARD_H 