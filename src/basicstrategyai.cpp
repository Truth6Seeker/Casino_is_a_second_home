#include "basicstrategyai.h"

BasicStrategyAI::BasicStrategyAI() {}

BasicStrategyAI::Action BasicStrategyAI::getAction(int playerScore,
                                                   int dealerUpCard,
                                                   bool isSoftHand,
                                                   bool canSplit) const {
  // First check for pairs if splitting is possible
  if (canSplit) {
    return getPairAction(playerScore / 2, dealerUpCard);
  }

  // Then check for soft hands
  if (isSoftHand) {
    return getSoftHandAction(playerScore, dealerUpCard);
  }

  // Finally, handle hard hands
  return getHardHandAction(playerScore, dealerUpCard);
}

BasicStrategyAI::Action BasicStrategyAI::getHardHandAction(
    int playerScore, int dealerUpCard) const {
  // 5-8: Always hit
  if (playerScore <= 8) {
    return Action::HIT;
  }

  // 17 and above: Always stand
  if (playerScore >= 17) {
    return Action::STAND;
  }

  // 9: Double against 3-6, otherwise hit
  if (playerScore == 9) {
    if (isDealerCardWeak(dealerUpCard)) {
      return Action::DOUBLE;
    }
    return Action::HIT;
  }

  // 10-11: Double against 2-9 (except 10 for 10), otherwise hit
  if (playerScore == 10 || playerScore == 11) {
    if (playerScore == 10 && dealerUpCard == 10) {
      return Action::HIT;
    }
    if (playerScore == 11 && dealerUpCard == 11) {
      return Action::HIT;
    }
    if (dealerUpCard >= 2 && dealerUpCard <= 9) {
      return Action::DOUBLE;
    }
    return Action::HIT;
  }

  // 12: Stand against 4-6, otherwise hit
  if (playerScore == 12) {
    if (isDealerCardVeryWeak(dealerUpCard)) {
      return Action::STAND;
    }
    return Action::HIT;
  }

  // 13-16: Stand against 2-6, otherwise hit
  if (playerScore >= 13 && playerScore <= 16) {
    if (isDealerCardWeak(dealerUpCard)) {
      return Action::STAND;
    }
    return Action::HIT;
  }

  return Action::HIT;  // Default to hit
}

BasicStrategyAI::Action BasicStrategyAI::getSoftHandAction(
    int playerScore, int dealerUpCard) const {
  // 13-17 (3-7): Hit, double against 5-6
  if (playerScore <= 17) {
    if (isDealerCardVeryWeak(dealerUpCard)) {
      return Action::DOUBLE;
    }
    return Action::HIT;
  }

  // 18 (8): Stand, hit against 9,10,A
  if (playerScore == 18) {
    if (isDealerCardStrong(dealerUpCard)) {
      return Action::HIT;
    }
    return Action::STAND;
  }

  // 19 (9) and above: Always stand
  return Action::STAND;
}

BasicStrategyAI::Action BasicStrategyAI::getPairAction(int pairValue,
                                                       int dealerUpCard) const {
  // A-A, 8-8: Always split except against A
  if (pairValue == 11 || pairValue == 8) {
    if (dealerUpCard == 11) {
      return Action::HIT;
    }
    return Action::SPLIT;
  }

  // 5-5, 10-10: Never split
  if (pairValue == 5 || pairValue == 10) {
    return Action::HIT;
  }

  // 4-4: Split only against 5-6
  if (pairValue == 4) {
    if (isDealerCardVeryWeak(dealerUpCard)) {
      return Action::SPLIT;
    }
    return Action::HIT;
  }

  // 9-9: Split except against 7,10,A
  if (pairValue == 9) {
    if (dealerUpCard == 7 || dealerUpCard == 10 || dealerUpCard == 11) {
      return Action::STAND;
    }
    return Action::SPLIT;
  }

  // 2-2, 3-3, 6-6, 7-7: Split against 2-7 (2-6 for 6-6)
  if (pairValue == 2 || pairValue == 3 || pairValue == 6 || pairValue == 7) {
    if (pairValue == 6) {
      if (dealerUpCard <= 6) {
        return Action::SPLIT;
      }
    } else {
      if (dealerUpCard <= 7) {
        return Action::SPLIT;
      }
    }
    return Action::HIT;
  }

  return Action::HIT;  // Default to hit
}

bool BasicStrategyAI::isSoftHand(const std::vector<int>& cards) const {
  bool hasAce = false;
  int sum = 0;

  for (int card : cards) {
    if (card == 11) {
      hasAce = true;
    }
    sum += card;
  }

  return hasAce && sum <= 21;
}

bool BasicStrategyAI::canDoubleDown(int playerScore) const {
  return playerScore >= 9 && playerScore <= 11;
}

bool BasicStrategyAI::shouldTakeInsurance() const {
  return false;  // Basic strategy recommends never taking insurance
}

bool BasicStrategyAI::isDealerCardWeak(int dealerCard) const {
  return dealerCard >= 2 && dealerCard <= 6;
}

bool BasicStrategyAI::isDealerCardStrong(int dealerCard) const {
  return dealerCard >= 9 && dealerCard <= 11;
}

bool BasicStrategyAI::isDealerCardVeryWeak(int dealerCard) const {
  return dealerCard >= 4 && dealerCard <= 6;
}

bool BasicStrategyAI::isDealerCardVeryStrong(int dealerCard) const {
  return dealerCard == 10 || dealerCard == 11;
}