#include "card.h"
#include <sstream>

Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

Suit Card::getSuit() const {
    return suit;
}

Rank Card::getRank() const {
    return rank;
}

int Card::getValue() const {
    if (rank == Rank::ACE) {
        return 11;  // Ace is worth 11 by default in blackjack
    } else if (rank >= Rank::JACK) {
        return 10;  // Face cards are worth 10
    }
    return static_cast<int>(rank);
}

std::string Card::toString() const {
    std::stringstream ss;
    
    // Add rank
    switch (rank) {
        case Rank::ACE: ss << "Ace"; break;
        case Rank::JACK: ss << "Jack"; break;
        case Rank::QUEEN: ss << "Queen"; break;
        case Rank::KING: ss << "King"; break;
        default: ss << static_cast<int>(rank);
    }
    
    ss << " of ";
    
    // Add suit
    switch (suit) {
        case Suit::HEARTS: ss << "Hearts"; break;
        case Suit::DIAMONDS: ss << "Diamonds"; break;
        case Suit::CLUBS: ss << "Clubs"; break;
        case Suit::SPADES: ss << "Spades"; break;
    }
    
    return ss.str();
}

std::string Card::toSymbol() const {
    std::stringstream ss;
    
    // Add rank
    switch (rank) {
        case Rank::ACE: ss << "A"; break;
        case Rank::JACK: ss << "J"; break;
        case Rank::QUEEN: ss << "Q"; break;
        case Rank::KING: ss << "K"; break;
        case Rank::TEN: ss << "10"; break;
        default: ss << static_cast<int>(rank);
    }
    
    // Add suit symbol
    switch (suit) {
        case Suit::HEARTS: ss << "♥"; break;
        case Suit::DIAMONDS: ss << "♦"; break;
        case Suit::CLUBS: ss << "♣"; break;
        case Suit::SPADES: ss << "♠"; break;
    }
    
    return ss.str();
} 