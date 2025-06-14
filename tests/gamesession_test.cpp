#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/gameSession.h"

#include <memory>

#include "../headers/blackjack.h"
#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("GameSession Tests") {
  TEST_CASE("Constructor Initialization") {
    auto player = std::make_shared<Player>("Test Player", 21, 1000.0);
    GameSession session(player);

    CHECK(session.getPlayer()->getId() == player->getId());
  }

  TEST_CASE("Game Start and End") {
    auto player = std::make_shared<Player>("Test Player", 21, 1000.0);
    auto game = std::make_shared<Blackjack>();
    GameSession session(player);

    SUBCASE("Start Game") {
      session.startGame(game);
      CHECK(session.isActive());
    }

    SUBCASE("End Game") {
      session.startGame(game);
      session.endGame();
      CHECK_FALSE(session.isActive());
    }
  }
}