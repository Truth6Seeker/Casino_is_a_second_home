#include "card.h"

#include <sstream>

Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

Suit Card::getSuit() const { return suit; }

Rank Card::getRank() const { return rank; }

int Card::getValue() const {
  if (rank == Rank::ACE) {
    return 11;
  }
  if (rank >= Rank::JACK) {
    return 10;
  }
  return static_cast<int>(rank);
}

std::string Card::toString() const {
  std::string result;

  switch (rank) {
    case Rank::ACE:
      result += "A";
      break;
    case Rank::JACK:
      result += "J";
      break;
    case Rank::QUEEN:
      result += "Q";
      break;
    case Rank::KING:
      result += "K";
      break;
    default:
      result += std::to_string(static_cast<int>(rank));
  }

  switch (suit) {
    case Suit::HEARTS:
      result += "♥";
      break;
    case Suit::DIAMONDS:
      result += "♦";
      break;
    case Suit::CLUBS:
      result += "♣";
      break;
    case Suit::SPADES:
      result += "♠";
      break;
  }

  return result;
}

std::string Card::toSymbol() const {
  std::stringstream ss;

  // Add rank
  switch (rank) {
    case Rank::ACE:
      ss << "A";
      break;
    case Rank::JACK:
      ss << "J";
      break;
    case Rank::QUEEN:
      ss << "Q";
      break;
    case Rank::KING:
      ss << "K";
      break;
    case Rank::TEN:
      ss << "10";
      break;
    default:
      ss << static_cast<int>(rank);
  }

  // Add suit symbol
  switch (suit) {
    case Suit::HEARTS:
      ss << "♥";
      break;
    case Suit::DIAMONDS:
      ss << "♦";
      break;
    case Suit::CLUBS:
      ss << "♣";
      break;
    case Suit::SPADES:
      ss << "♠";
      break;
  }

  return ss.str();
}