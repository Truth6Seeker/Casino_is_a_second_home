#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/casino.h"

#include <memory>

#include "../headers/player.h"
#include "doctest.h"

TEST_SUITE("Casino Tests") {
  TEST_CASE("Casino Initialization") {
    Casino casino("Test Casino");
    CHECK(casino.getName() == "Test Casino");
  }

  TEST_CASE("Player Registration") {
    Casino casino("Test Casino");
    auto player = casino.registerPlayer("Alice", 25, 1000.0);
    CHECK(player->getName() == "Alice");
    CHECK(player->getAge() == 25);
    CHECK(player->getBalance() == 1000.0);
  }

  TEST_CASE("Game Session Creation") {
    Casino casino("Test Casino");
    auto player = casino.registerPlayer("Bob", 30, 500.0);
    auto session = casino.createGameSession(player->getId());
    CHECK(session->getPlayer()->getId() == player->getId());
  }

  TEST_CASE("Underage Player Registration Fails") {
    Casino casino("Test Casino");
    auto player = casino.registerPlayer("Charlie", 16, 100.0);
    CHECK(player->getAge() < 18);
  }
}