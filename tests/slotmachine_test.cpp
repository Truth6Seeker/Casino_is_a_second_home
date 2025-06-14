#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/slotmachine.h"

#include <memory>

#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("SlotMachine Public Interface Tests") {
  TEST_CASE("Constructor initializes correctly") {
    SlotMachine game;
    CHECK_FALSE(game.isGameActive());
    CHECK_EQ(game.getTotalRoundsPlayed(), 0);
    CHECK_EQ(game.getTotalAmountWagered(), 0.0);
    CHECK_EQ(game.getTotalAmountWon(), 0.0);
  }

  TEST_CASE("Game start initializes correctly") {
    SlotMachine game;
    auto player = std::make_shared<Player>("Test", 21, 1000.0);
    game.startGame(player);
    CHECK(game.isGameActive());
  }

  TEST_CASE("Game name is correct") {
    SlotMachine game;
    CHECK_EQ(game.getGameName(), "Slot Machine");
  }

  TEST_CASE("House edge is correct") {
    SlotMachine game;
    CHECK_EQ(game.getHouseEdge(), 0.10);  // 10% house edge
  }
}