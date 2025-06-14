#pragma once
#include <string>
#include <vector>

class BasicStrategyAI {
 public:
  enum class Action { HIT, STAND, DOUBLE, SPLIT, SURRENDER };

  BasicStrategyAI();

  // Main decision making function
  Action getAction(int playerScore, int dealerUpCard, bool isSoftHand,
                   bool canSplit) const;

  // Helper functions
  bool isSoftHand(const std::vector<int>& cards) const;
  bool canDoubleDown(int playerScore) const;
  bool shouldTakeInsurance() const;

 private:
  // Strategy helper functions
  Action getHardHandAction(int playerScore, int dealerUpCard) const;
  Action getSoftHandAction(int playerScore, int dealerUpCard) const;
  Action getPairAction(int pairValue, int dealerUpCard) const;

  // Utility functions
  bool isDealerCardWeak(int dealerCard) const;
  bool isDealerCardStrong(int dealerCard) const;
  bool isDealerCardVeryWeak(int dealerCard) const;
  bool isDealerCardVeryStrong(int dealerCard) const;
};