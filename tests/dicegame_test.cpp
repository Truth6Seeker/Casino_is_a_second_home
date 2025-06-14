#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/dicegame.h"

#include <memory>

#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("DiceGame Public Interface Tests") {
  TEST_CASE("Constructor initializes correctly") {
    DiceGame game;
    CHECK_FALSE(game.isGameActive());
    CHECK_EQ(game.getTotalRoundsPlayed(), 0);
    CHECK_EQ(game.getTotalAmountWagered(), 0.0);
    CHECK_EQ(game.getTotalAmountWon(), 0.0);
  }

  TEST_CASE("Game start initializes correctly") {
    DiceGame game;
    auto player = std::make_shared<Player>("Test", 21, 1000.0);
    game.startGame(player);
    CHECK(game.isGameActive());
  }

  TEST_CASE("Game name is correct") {
    DiceGame game;
    CHECK_EQ(game.getGameName(), "Dice Roll");
  }

  TEST_CASE("House edge is correct") {
    DiceGame game;
    CHECK_EQ(game.getHouseEdge(), 0.1111);  // 11.11% house edge
  }
}