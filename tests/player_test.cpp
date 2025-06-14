#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/player.h"

#include <memory>

#include "doctest.h"

TEST_SUITE("Player Tests") {
  TEST_CASE("Constructor Initialization") {
    Player player("John Doe", 25, 1000.0);

    CHECK(player.getName() == "John Doe");
    CHECK(player.getAge() == 25);
    CHECK(player.getBalance() == 1000.0);
    CHECK(player.getId() > 0);
  }

  TEST_CASE("Balance Operations") {
    Player player("Jane Doe", 30, 500.0);

    SUBCASE("Deposit") {
      player.deposit(100.0);
      CHECK(player.getBalance() == 600.0);
    }

    SUBCASE("Withdraw") {
      player.withdraw(200.0);
      CHECK(player.getBalance() == 300.0);
    }

    SUBCASE("Insufficient Balance") {
      CHECK_FALSE(player.withdraw(
          1000.0));  // Should return false for insufficient balance
      CHECK(player.getBalance() == 500.0);  // Balance should remain unchanged
    }
  }

  TEST_CASE("Player Verification") {
    Player adult("Adult", 21, 1000.0);
    Player underage("Underage", 17, 1000.0);

    CHECK(adult.getAge() >= 18);
    CHECK(underage.getAge() < 18);
  }
}