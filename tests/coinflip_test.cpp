#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/coinflip.h"

#include <memory>

#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("CoinFlip Public Interface Tests") {
  TEST_CASE("Constructor initializes correctly") {
    CoinFlip game;
    CHECK_FALSE(game.isGameActive());
    CHECK_EQ(game.getTotalRoundsPlayed(), 0);
    CHECK_EQ(game.getTotalAmountWagered(), 0.0);
    CHECK_EQ(game.getTotalAmountWon(), 0.0);
  }

  TEST_CASE("Game start initializes correctly") {
    CoinFlip game;
    auto player = std::make_shared<Player>("Test", 21, 1000.0);
    game.startGame(player);
    CHECK(game.isGameActive());
  }

  TEST_CASE("Game name is correct") {
    CoinFlip game;
    CHECK_EQ(game.getGameName(), "Coin Flip");
  }

  TEST_CASE("House edge is correct") {
    CoinFlip game;
    CHECK_EQ(game.getHouseEdge(), 0.025);  // 2.5% house edge
  }
}