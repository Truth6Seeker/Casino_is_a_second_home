#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/leaderboard.h"

#include <filesystem>

#include "doctest.h"

TEST_SUITE("Leaderboard Public Interface Tests") {
  TEST_CASE("Leaderboard operations work correctly") {
    // Clean up the database before the test
    std::filesystem::remove("data/leaderboard.db");

    Leaderboard leaderboard;

    // Add some players
    leaderboard.addOrUpdatePlayer("Player1", 1000.0, 5, 10);
    leaderboard.addOrUpdatePlayer("Player2", 2000.0, 8, 15);
    leaderboard.addOrUpdatePlayer("Player3", 500.0, 2, 5);

    // Get top players
    auto top = leaderboard.getTopPlayers();

    // Check if players are sorted by balance
    CHECK_EQ(top[0].name, "Player2");
    CHECK_EQ(top[0].balance, 2000.0);
    CHECK_EQ(top[1].name, "Player1");
    CHECK_EQ(top[1].balance, 1000.0);
    CHECK_EQ(top[2].name, "Player3");
    CHECK_EQ(top[2].balance, 500.0);
  }

  TEST_CASE("Player stats are updated correctly") {
    // Clean up the database before the test
    std::filesystem::remove("data/leaderboard.db");

    Leaderboard leaderboard;

    // Add initial stats
    leaderboard.addOrUpdatePlayer("Player1", 1000.0, 5, 10);

    // Update stats with higher values
    leaderboard.addOrUpdatePlayer("Player1", 1500.0, 7, 12);

    // Add another player with higher balance
    leaderboard.addOrUpdatePlayer("Player2", 2000.0, 8, 15);

    auto top = leaderboard.getTopPlayers();

    // Player2 should be first due to higher balance
    CHECK_EQ(top[0].name, "Player2");
    CHECK_EQ(top[0].balance, 2000.0);
    CHECK_EQ(top[0].wins, 8);
    CHECK_EQ(top[0].games_played, 15);

    // Player1 should be second
    CHECK_EQ(top[1].name, "Player1");
    CHECK_EQ(top[1].balance, 1500.0);
    CHECK_EQ(top[1].wins, 7);
    CHECK_EQ(top[1].games_played, 12);
  }
}