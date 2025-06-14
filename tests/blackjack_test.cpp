#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/blackjack.h"

#include <memory>

#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("Blackjack Public Interface Tests") {
  TEST_CASE("Constructor initializes correctly") {
    Blackjack game;
    CHECK_FALSE(game.isGameActive());
    CHECK_EQ(game.getTotalRoundsPlayed(), 0);
    CHECK_EQ(game.getTotalAmountWagered(), 0.0);
    CHECK_EQ(game.getTotalAmountWon(), 0.0);
  }

  TEST_CASE("Game start initializes correctly") {
    Blackjack game;
    auto player = std::make_shared<Player>("Test", 21, 1000.0);
    game.startGame(player);
    CHECK(game.isGameActive());
  }

  TEST_CASE("AI control works correctly") {
    Blackjack game;
    CHECK_FALSE(game.isUsingAI());
    game.setUseAI(true);
    CHECK(game.isUsingAI());
    game.setUseAI(false);
    CHECK_FALSE(game.isUsingAI());
  }

  TEST_CASE("Game name is correct") {
    Blackjack game;
    CHECK_EQ(game.getGameName(), "Blackjack");
  }

  TEST_CASE("House edge is correct") {
    Blackjack game;
    CHECK_EQ(game.getHouseEdge(), 0.05);  // 5% house edge
  }
}