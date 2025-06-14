#include <iomanip>
#include <iostream>
#include <limits>

#include "../headers/blackjack.h"
#include "../headers/casino.h"
#include "../headers/coinflip.h"
#include "../headers/dicegame.h"
#include "../headers/leaderboard.h"
#include "../headers/roulette.h"
#include "../headers/slotmachine.h"

const double SECURITY_ALERT_BALANCE = 1000000.0;
const double VIP_THRESHOLD = 77777.0;

void clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayVIPMessage() {
  std::cout
      << "\n╔════════════════════════════════════════════════════════════╗\n";
  std::cout
      << "║                      🎰 VIP STATUS 🎰                      ║\n";
  std::cout
      << "║                                                            ║\n";
  std::cout
      << "║  Congratulations! You are a valued VIP player!            ║\n";
  std::cout
      << "║  Enjoy exclusive benefits and premium gaming experience!   ║\n";
  std::cout
      << "║                                                            ║\n";
  std::cout
      << "╚════════════════════════════════════════════════════════════╝\n\n";
}

void playBlackjack(std::shared_ptr<GameSession> session,
                   int& session_games_played, int& session_wins) {
  auto blackjack = std::make_shared<Blackjack>();

  std::cout << "\n=== Welcome to Blackjack! ===\n";
  std::cout << "Rules:\n- Try to get closer to 21 than dealer\n- Face cards = "
               "10, Ace = 1 or 11\n- Dealer stands on 17\n\n";

  // Вопрос про AI ДО старта игры
  char useAI;
  while (true) {
    std::cout << "Do you want to use the Basic Strategy AI? (y/n): ";
    if (std::cin >> useAI) {
      useAI = tolower(useAI);
      if (useAI == 'y' || useAI == 'n') {
        break;
      }
    }
    std::cout << "Invalid input! Please enter y or n\n";
    clearInputBuffer();
  }
  blackjack->setUseAI(useAI == 'y');
  if (useAI == 'y') {
    std::cout << "Basic Strategy AI enabled. The AI will make optimal "
                 "decisions based on basic strategy.\n";
  }

  while (true) {
    double balance = session->getPlayer()->getBalance();
    std::cout << "Current balance: $" << balance << "\n";

    if (balance <= 0) {
      std::cout << "You're out of money! Game over.\n";
      break;
    }

    session->startGame(blackjack);
    blackjack->startGame(session->getPlayer());
    RoundResult result = blackjack->playRoundWithResult();

    if (result == RoundResult::EXIT) break;

    // Обновляем сессионную статистику
    session_games_played++;
    if (result == RoundResult::WIN) session_wins++;

    std::cout << "New balance: $" << session->getPlayer()->getBalance()
              << "\n\n";
  }
}

void playRoulette(std::shared_ptr<GameSession> session) {
  auto roulette = std::make_shared<Roulette>();
  session->startGame(roulette);
}

void playDiceGame(std::shared_ptr<GameSession> session) {
  auto diceGame = std::make_shared<DiceGame>();
  session->startGame(diceGame);

  std::cout << "\n=== Welcome to Dice Roll! ===\n";
  std::cout << "Rules:\n- Bet on High (4-6) or Low (1-3)\n- Win pays 1.8x your "
               "bet\n\n";

  while (true) {
    // Show current balance
    double balance = session->getPlayer()->getBalance();
    std::cout << "Current balance: $" << balance << "\n";

    // Check if player can continue
    if (balance <= 0) {
      std::cout << "You're out of money! Game over.\n";
      break;
    }

    // Get bet amount
    double betAmount;
    while (true) {
      std::cout << "Enter bet amount (0 to quit): $";
      if (std::cin >> betAmount) {
        if (betAmount == 0) {
          std::cout << "Thanks for playing!\n";
          return;
        }
        if (betAmount > 0 && betAmount <= balance) {
          break;
        }
      }
      std::cout << "Invalid amount! Please enter a value between 0 and "
                << balance << "\n";
      clearInputBuffer();
    }

    // Get high/low choice
    char choice;
    while (true) {
      std::cout << "Bet on (H)igh or (L)ow? ";
      if (std::cin >> choice) {
        choice = toupper(choice);
        if (choice == 'H' || choice == 'L') {
          break;
        }
      }
      std::cout << "Invalid choice! Please enter H or L\n";
      clearInputBuffer();
    }

    // 1. First try to place the bet (will deduct from balance)
    if (!diceGame->placeBet(betAmount, choice == 'H')) {
      std::cout << "Failed to place bet! Please check your balance.\n";
      continue;  // Skip to next round if bet failed
    }

    // 2. Play the round (bet was successfully placed)
    diceGame->playRound();

    // 3. Show result - balance was already updated by placeBet()
    int result = diceGame->getLastRoll();
    std::cout << "\nDice rolled: " << result << " - You "
              << (result >= 4 && choice == 'H' || result <= 3 && choice == 'L'
                      ? "WON!"
                      : "LOST!")
              << "\n";

    // 4. Show updated balance (automatically reflects win/loss)
    std::cout << "New balance: $" << session->getPlayer()->getBalance()
              << "\n\n";
  }
}

void playCoinFlip(std::shared_ptr<GameSession> session) {
  auto coinFlip = std::make_shared<CoinFlip>();
  session->startGame(coinFlip);

  std::cout << "\n=== Welcome to Coin Flip! ===\n";
  std::cout << "Rules:\n- Bet on Heads or Tails\n- Win pays 1.95x your bet\n\n";

  while (true) {
    // Show current balance
    double balance = session->getPlayer()->getBalance();
    std::cout << "Current balance: $" << balance << "\n";

    // Check if player can continue
    if (balance <= 0) {
      std::cout << "You're out of money! Game over.\n";
      break;
    }

    // Get bet amount
    double betAmount;
    while (true) {
      std::cout << "Enter bet amount (0 to quit): $";
      if (std::cin >> betAmount) {
        if (betAmount == 0) {
          std::cout << "Thanks for playing!\n";
          return;
        }
        if (betAmount > 0 && betAmount <= balance) {
          break;
        }
      }
      std::cout << "Invalid amount! Please enter a value between 0 and "
                << balance << "\n";
      clearInputBuffer();
    }

    // Get heads/tails choice
    char choice;
    while (true) {
      std::cout << "Bet on (H)eads or (T)ails? ";
      if (std::cin >> choice) {
        choice = toupper(choice);
        if (choice == 'H' || choice == 'T') {
          break;
        }
      }
      std::cout << "Invalid choice! Please enter H or T\n";
      clearInputBuffer();
    }

    // Place the bet
    if (!coinFlip->placeBet(betAmount, choice == 'H')) {
      std::cout << "Failed to place bet! Please check your balance.\n";
      continue;
    }

    // Play the round
    coinFlip->playRound();

    // Show result
    std::cout << "\nCoin landed on: " << coinFlip->getLastResultString()
              << "\n";
    std::cout << "You "
              << (coinFlip->getLastResult() == (choice == 'H' ? 1 : 0)
                      ? "WON!"
                      : "LOST!")
              << "\n";

    // Show updated balance
    std::cout << "New balance: $" << session->getPlayer()->getBalance()
              << "\n\n";
  }
}

void playSlotMachine(std::shared_ptr<GameSession> session) {
  auto slotMachine = std::make_shared<SlotMachine>();
  session->startGame(slotMachine);

  std::cout << "\n=== Welcome to Slot Machine! ===\n";
  std::cout << "Rules:\n";
  std::cout << "- Place your bet\n";
  std::cout << "- Spin the reels\n";
  std::cout << "- Match symbols on the payline to win\n";
  std::cout << "Symbols and payouts:\n";
  std::cout << "Diamond (D): 3x = 100x, 2x = 10x\n";
  std::cout << "Seven (7): 3x = 50x, 2x = 5x\n";
  std::cout << "Bell (B): 3x = 20x, 2x = 3x\n";
  std::cout << "Star (S): 3x = 15x, 2x = 2x\n";
  std::cout << "Orange (O): 3x = 10x\n";
  std::cout << "Lemon (L): 3x = 8x\n";
  std::cout << "Cherry (C): 3x = 5x, 2x = 2x, 1x = 1x\n\n";

  while (true) {
    double balance = session->getPlayer()->getBalance();
    std::cout << "Current balance: $" << balance << "\n";

    if (balance <= 0) {
      std::cout << "You're out of money! Game over.\n";
      break;
    }

    // Get bet amount
    double betAmount;
    while (true) {
      std::cout << "Enter bet amount (0 to quit, -1 for all-in): $";
      if (std::cin >> betAmount) {
        if (betAmount == 0) {
          std::cout << "Thanks for playing!\n";
          return;
        }
        if (betAmount == -1) {
          slotMachine->placeAllInBet();
          break;
        }
        if (betAmount > 0 && betAmount <= balance) {
          if (!slotMachine->placeBet(betAmount)) {
            std::cout << "Failed to place bet! Please check your balance.\n";
            continue;
          }
          break;
        }
      }
      std::cout << "Invalid amount! Please enter a value between 0 and "
                << balance << "\n";
      clearInputBuffer();
    }

    // Play the round
    slotMachine->playRound();

    // Show updated balance
    std::cout << "New balance: $" << session->getPlayer()->getBalance()
              << "\n\n";
  }
}

int main() {
  Leaderboard leaderboard;
  Casino myCasino("Lucky Dice Casino");

  // Register and verify player
  std::string name;
  int age;
  double initialDeposit;

  std::cout << "=== Welcome to " << myCasino.getName() << " ===\n";
  std::cout << "Enter your name: ";
  std::getline(std::cin, name);

  std::cout << "Enter your age: ";
  while (!(std::cin >> age) || age < 18) {
    std::cout << "Invalid age! You must be 18+. Please enter your age: ";
    clearInputBuffer();
  }

  std::cout << "Enter initial deposit: $";
  while (!(std::cin >> initialDeposit) || initialDeposit <= 0) {
    std::cout << "Invalid amount! Please enter a positive value: $";
    clearInputBuffer();
  }

  auto player = myCasino.registerPlayer(name, age, initialDeposit);
  player->verify();

  // Сессионная статистика
  int session_games_played = 0;
  int session_wins = 0;

  // Create game session and play
  auto session = myCasino.createGameSession(player->getId());
  while (true) {
    // Display VIP status if applicable
    if (player->getBalance() >= VIP_THRESHOLD) {
      displayVIPMessage();
    }

    std::cout << "\n=== Game Selection ===\n";
    std::cout << "1. Play Dice Game\n";
    std::cout << "2. Play Blackjack\n";
    std::cout << "3. Play Roulette\n";
    std::cout << "4. Play Coin Flip\n";
    std::cout << "5. Play Slot Machine\n";
    std::cout << "6. Show Leaderboard\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";

    int choice;
    if (std::cin >> choice) {
      clearInputBuffer();
      switch (choice) {
        case 1:
          playDiceGame(session);
          break;
        case 2:
          playBlackjack(session, session_games_played, session_wins);
          break;
        case 3:
          playRoulette(session);
          break;
        case 4:
          playCoinFlip(session);
          break;
        case 5:
          playSlotMachine(session);
          break;
        case 6: {
          auto top = leaderboard.getTopPlayers();
          std::cout << "\n=== Leaderboard ===\n";
          std::cout << "Name | Balance | Games Played | Wins\n";
          for (const auto& entry : top) {
            std::cout << entry.name << " | $" << entry.balance << " | "
                      << entry.games_played << " | " << entry.wins << "\n";
          }
          break;
        }
        case 7:
          leaderboard.addOrUpdatePlayer(player->getName(), player->getBalance(),
                                        session_wins, session_games_played);
          std::cout << "Thanks for playing!\n";
          return 0;
        default:
          std::cout << "Invalid choice!\n";
      }
    } else {
      clearInputBuffer();
      std::cout << "Invalid input! Please enter a number between 1 and 7\n";
    }

    // Показываем баланс после каждой игры
    std::cout << "\nYour current balance: $" << std::fixed
              << std::setprecision(2) << player->getBalance() << "\n";

    // SECURITY ALERT
    if (player->getBalance() >= SECURITY_ALERT_BALANCE) {
      std::cout << "\n!!! SECURITY ALERT !!!\n";
      std::cout << "Casino investigation started for player: "
                << player->getName() << "\n";
      std::cout << "Reason: suspiciously high balance: $"
                << player->getBalance() << "\n";
      leaderboard.addOrUpdatePlayer(player->getName(), player->getBalance(),
                                    session_wins, session_games_played);
      std::cout << "Game session terminated due to investigation.\n";
      return 0;
    }
  }

  // Show final results
  std::cout << "\n=== Game Over ===\n";
  std::cout << "Final balance: $" << std::fixed << std::setprecision(2)
            << player->getBalance() << "\n";
  std::cout << "Thanks for playing!\n";

  return 0;
}