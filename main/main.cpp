#include "../headers/casino.h"
#include "../headers/dicegame.h"
#include "../headers/blackjack.h"
#include "../headers/Casino.h"
#include "../headers/DiceGame.h"
#include "../headers/CoinFlip.h"
#include "../headers/Slotmachine.h"
#include "../headers/russianRoulette.h"
#include <iomanip>
#include <iostream>
#include <limits>

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void playBlackjack(std::shared_ptr<GameSession> session)
{
    std::cout << "\n=== Welcome to Blackjack! ===\n";
    std::cout << "Rules:\n- Try to get closer to 21 than dealer\n- Face cards = 10, Ace = 1 or 11\n- Dealer stands on 17\n\n";

    auto blackjack = std::make_shared<Blackjack>();
    session->startGame(blackjack);

    while (true)
    {
        double balance = session->getPlayer()->getBalance();
        std::cout << "Current balance: $" << balance << "\n";

        if (balance <= 0)
        {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        double betAmount;
        while (true)
        {
            std::cout << "Enter bet amount (0 to quit): $";
            if (std::cin >> betAmount)
            {
                if (betAmount == 0)
                {
                    std::cout << "Thanks for playing!\n";
                    return;
                }
                if (betAmount > 0 && betAmount <= balance)
                {
                    break;
                }
            }
            std::cout << "Invalid amount! Please enter a value between 0 and " << balance << "\n";
            clearInputBuffer();
        }

        // Начинаем игру (ставка будет обрабатываться внутри Blackjack)
        blackjack->startGame(session->getPlayer());
        blackjack->playRound();

        std::cout << "New balance: $" << session->getPlayer()->getBalance() << "\n\n";
    }
}

// Smart rounding function
double casinoRound(double value)
{
    const double EPSILON = 0.001; // Threshold for considering as equal
    const double STEP = 0.01;     // Smallest money unit we care about (1 cent)

    // Check if value is very close to a whole cent
    double rounded = std::round(value / STEP) * STEP;
    if (std::abs(value - rounded) < EPSILON)
    {
        return rounded;
    }
    return value; // Return original if not near any "clean" value
}

void playCoinFlipGame(std::shared_ptr<GameSession> session)
{
    auto coinGame = std::make_shared<CoinFlip>();
    session->startGame(coinGame);

    std::cout << "\n=== Welcome to Coin Flip! ===\n";
    std::cout << "Rules:\n- Bet on Heads or Tails\n- Win pays 1.95x your bet\n\n";

    while (true)
    {
        // Show current balance
        double balance = session->getPlayer()->getBalance();
        std::cout << "Current balance: $" << casinoRound(balance) << "\n";

        // Check if player can continue
        if (balance <= 0)
        {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        // Get bet amount
        double betAmount;
        while (true)
        {
            std::cout << "Enter bet amount (0 to quit): $";
            if (std::cin >> betAmount)
            {
                if (betAmount == 0)
                {
                    std::cout << "Thanks for playing!\n";
                    return;
                }
                if (betAmount > 0 && casinoRound(balance - betAmount) >= 0)
                {
                    break;
                }
            }
            std::cout << "Invalid amount! Please enter a value between 0 and " << balance << "\n";
            clearInputBuffer();
        }

        // Get heads/tails choice
        char choice;
        while (true)
        {
            std::cout << "Bet on (H)eads or (T)ails? ";
            if (std::cin >> choice)
            {
                choice = toupper(choice);
                if (choice == 'H' || choice == 'T')
                {
                    break;
                }
            }
            std::cout << "Invalid choice! Please enter H or T\n";
            clearInputBuffer();
        }

        // Place bet
        if (!coinGame->placeBet(betAmount, choice == 'H'))
        {
            std::cout << "Failed to place bet! Please check your balance.\n";
            continue;
        }

        // Play the round
        coinGame->playRound();

        // Show result
        std::string result = coinGame->getLastResultString();
        std::cout << "\nCoin landed: " << result << " - You "
                  << ((choice == 'H' && result == "HEADS") ||
                              (choice == 'T' && result == "TAILS")
                          ? "WON!"
                          : "LOST!")
                  << "\n";

        // Show updated balance
        std::cout << "New balance: $" << casinoRound(session->getPlayer()->getBalance()) << "\n\n";
    }
}

void playDiceGame(std::shared_ptr<GameSession> session)
{
    auto diceGame = std::make_shared<DiceGame>();
    session->startGame(diceGame);

    std::cout << "\n=== Welcome to Dice Roll! ===\n";
    std::cout << "Rules:\n- Bet on High (4-6) or Low (1-3)\n- Win pays 1.8x your bet\n\n";

    while (true)
    {
        // Show current balance
        double balance = session->getPlayer()->getBalance();
        std::cout << "Current balance: $" << casinoRound(balance) << "\n";

        // Check if player can continue
        if (balance <= 0)
        {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        // Get bet amount
        double betAmount;
        while (true)
        {
            std::cout << "Enter bet amount (0 to quit): $";
            if (std::cin >> betAmount)
            {
                if (betAmount == 0)
                {
                    std::cout << "Thanks for playing!\n";
                    return;
                }
                if (betAmount > 0 && casinoRound(balance - betAmount) >= 0)
                {
                    break;
                }
            }
            std::cout << "Invalid amount! Please enter a value between 0 and " << balance << "\n";
            clearInputBuffer();
        }

        // Get high/low choice
        char choice;
        while (true)
        {
            std::cout << "Bet on (H)igh or (L)ow? ";
            if (std::cin >> choice)
            {
                choice = toupper(choice);
                if (choice == 'H' || choice == 'L')
                {
                    break;
                }
            }
            std::cout << "Invalid choice! Please enter H or L\n";
            clearInputBuffer();
        }

        // 1. First try to place the bet (will deduct from balance)
        if (!diceGame->placeBet(betAmount, choice == 'H'))
        {
            std::cout << "Failed to place bet! Please check your balance.\n";
            continue; // Skip to next round if bet failed
        }

        // 2. Play the round (bet was successfully placed)
        diceGame->playRound();

        // 3. Show result - balance was already updated by placeBet()
        int result = diceGame->getLastRoll();
        std::cout << "\nDice rolled: " << result << " - You "
                  << (result >= 4 && choice == 'H' || result <= 3 && choice == 'L' ? "WON!" : "LOST!")
                  << "\n";

        // 4. Show updated balance (automatically reflects win/loss)
        std::cout << "New balance: $" << casinoRound(session->getPlayer()->getBalance()) << "\n\n";
    }
}

void playRussianRoulette(std::shared_ptr<GameSession> session)
{
    auto rrGame = std::make_shared<RussianRoulette>();
    if (!session->startGame(rrGame))
    {
        std::cout << "Cannot start game. Another game is active.\n";
        return;
    }

    std::cout << "\n=== WELCOME TO RUSSIAN ROULETTE ===\n";
    std::cout << "The ULTIMATE game of chance and nerve!\n";
    std::cout << "-----------------------------------\n";
    std::cout << "How it works:\n";
    std::cout << "1. Choose your risk level (1-5 bullets)\n";
    std::cout << "2. Place your bet - the house matches it\n";
    std::cout << "3. Take turns pulling the trigger\n";
    std::cout << "4. Survive to win 1.2x-5.0x the pot!\n";
    std::cout << "5. Escape option: Buy your way out mid-game\n";
    std::cout << "-----------------------------------\n\n";

    while (true)
    {
        double balance = session->getPlayer()->getBalance();
        std::cout << "Current balance: $" << casinoRound(balance) << "\n";

        if (balance <= 0)
        {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        // Set risk level
        int riskLevel;
        while (true)
        {
            std::cout << "\nChoose your risk (1-5 bullets, 0 to quit): ";
            if (std::cin >> riskLevel)
            {
                if (riskLevel == 0)
                {
                    std::cout << "Thanks for playing!\n";
                    session->endGame();
                    return;
                }
                if (riskLevel >= 1 && riskLevel <= 5)
                {
                    rrGame->setRiskLevel(riskLevel);
                    std::cout << "Loaded " << riskLevel << " bullet"
                              << (riskLevel > 1 ? "s" : "") << "!\n";
                    break;
                }
            }
            std::cout << "Invalid input! Please enter 1-5.\n";
            clearInputBuffer();
        }

        // Place initial bet
        double betAmount;
        while (true)
        {
            std::cout << "Enter your bet (0 to quit): $";
            if (std::cin >> betAmount)
            {
                if (betAmount == 0)
                {
                    std::cout << "Thanks for playing!\n";
                    session->endGame();
                    return;
                }
                if (betAmount > 0 && betAmount <= balance)
                {
                    if (rrGame->placeBet(betAmount))
                    {
                        std::cout << "House matches your bet! Total pot: $"
                                  << std::fixed << std::setprecision(2)
                                  << betAmount * 2 << "\n";
                        break;
                    }
                    else
                    {
                        std::cout << "Failed to place bet. Please try again.\n";
                    }
                }
            }
            std::cout << "Invalid amount! Please enter between 0 and "
                      << balance << "\n";
            clearInputBuffer();
        }

        // Game loop - completely rewritten
        while (rrGame->isGameActive() && !rrGame->isGameOver())
        {
            // Display state
            std::cout << "\n======================\n";
            std::cout << "  Chamber: " << rrGame->getChamberState() << "\n";
            std::cout << "  Bullets: " << rrGame->getBulletsRemaining() << " remain\n";
            std::cout << "  Multiplier: " << std::fixed << std::setprecision(1)
                      << rrGame->getCurrentMultiplier() << "x\n";
            std::cout << "======================\n";

            if (rrGame->isPlayerTurn())
            {
                char action;
                double escapeAmount = 0;
                bool validAction = false;

                while (!validAction)
                {
                    std::cout << "\nYour turn: (P)ull trigger, (E)scape: ";
                    std::cin >> action;
                    action = toupper(action);

                    if (action == 'E')
                    {
                        double minEscape = betAmount * 0.5;
                        std::cout << "Enter escape amount (min $"
                                  << std::fixed << std::setprecision(2)
                                  << minEscape << "): $";
                        if (!(std::cin >> escapeAmount))
                        {
                            std::cout << "Invalid amount!\n";
                            clearInputBuffer();
                            continue;
                        }

                        // Validate escape amount
                        if (escapeAmount < minEscape)
                        {
                            std::cout << "Escape amount must be at least $"
                                      << minEscape << "!\n";
                            continue;
                        }
                    }

                    if (action == 'P')
                    {
                        validAction = rrGame->pullTrigger();
                    }
                    else if (action == 'E')
                    {
                        validAction = rrGame->makeEscape(escapeAmount);
                    }
                    else
                    {
                        std::cout << "Invalid choice! Please enter P or E\n";
                    }

                    if (!validAction)
                    {
                        std::cout << "Action failed! Please try again.\n";
                    }
                }
            }
            else // Dealer's turn
            {
                std::cout << "\nDealer's turn...\n";
                std::cout << "Dealer pulls the trigger!\n";
                rrGame->pullTrigger();
            }

            // Break immediately if game ended
            if (rrGame->isGameOver())
                break;
        }

        // Show result
        if (rrGame->didPlayerSurvive())
        {
            std::cout << "\n\nYOU SURVIVED! ";
            if (rrGame->isPlayerTurn())
            {
                std::cout << "Dealer didn't make it!\n";
                std::cout << "You won $"
                          << std::fixed << std::setprecision(2)
                          << rrGame->getCurrentMultiplier() * betAmount * 2
                          << "!\n";
            }
            else
            {
                std::cout << "You escaped with your life!\n";
            }
        }
        else
        {
            std::cout << "\n\nGAME OVER! You didn't survive this round.\n";
        }

        // Get actual balance from player object
        double newBalance = session->getPlayer()->getBalance();
        std::cout << "New balance: $" << casinoRound(newBalance) << "\n\n";

        // Reset for next round
        rrGame->resetRoundState();
    }
    session->endGame();
}

void playSlotGame(std::shared_ptr<GameSession> session)
{
    auto slotGame = std::make_shared<SlotMachine>();
    session->startGame(slotGame);

    std::cout << "\n=== Welcome to Slot Machine! ===\n";
    std::cout << "Rules:\n- Bet any amount\n- Spin to match symbols on the center payline\n";
    std::cout << "- Winning combinations pay different amounts\n";
    std::cout << "- Type 'all' to bet your entire balance\n";
    std::cout << "- C = Cherry, L = Lemon, O = Orange \n";
    std::cout << "-- S = Star, B = Bell, 7 = Seven ;), D = Diamond \n\n";

    while (true)
    {
        // Show current balance
        double balance = session->getPlayer()->getBalance();
        std::cout << "Current balance: $" << casinoRound(balance) << "\n";

        // Check if player can continue
        if (balance <= 0)
        {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        // Get bet amount
        double betAmount = 0;
        std::string input;
        bool validInput = false;

        while (!validInput)
        {
            std::cout << "Enter bet amount (0 to quit, 'all' for all-in): $";
            std::cin >> input;

            if (input == "0")
            {
                std::cout << "Thanks for playing!\n";
                return;
            }

            if (input == "all")
            {
                slotGame->placeAllInBet();
                validInput = true;
                std::cout << "All-in bet placed! $" << casinoRound(balance) << " on the line!\n";
            }
            else
            {
                try
                {
                    betAmount = std::stod(input);
                    if (betAmount > 0 && betAmount <= balance)
                    {
                        if (slotGame->placeBet(betAmount))
                        {
                            validInput = true;
                        }
                        else
                        {
                            std::cout << "Failed to place bet! Please check your balance.\n";
                        }
                    }
                    else
                    {
                        std::cout << "Invalid amount! Please enter a value between 0 and "
                                  << balance << "\n";
                    }
                }
                catch (...)
                {
                    std::cout << "Invalid input! Please enter a number or 'all'\n";
                }
            }
            clearInputBuffer();
        }

        // Play the round
        slotGame->playRound();

        // Show updated balance
        std::cout << "New balance: $" << casinoRound(session->getPlayer()->getBalance()) << "\n\n";
    }
}

int main()
{
    Casino myCasino("Lucky Dice Casino");

    // Register and verify player
    std::string name;
    int age;
    double initialDeposit;

    std::cout << "=== Welcome to " << myCasino.getName() << " ===\n";
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your age: ";
    while (!(std::cin >> age) || age < 18)
    {
        std::cout << "Invalid or unacceptable age! Please enter your age: ";
        clearInputBuffer();
    }

    std::cout << "Enter initial deposit: $";
    while (!(std::cin >> initialDeposit) || initialDeposit <= 0)
    {
        std::cout << "Invalid amount! Please enter a positive value: $";
        clearInputBuffer();
    }

    auto player = myCasino.registerPlayer(name, age, initialDeposit);
    player->verify();

    // Create game session and play
    auto session = myCasino.createGameSession(player->getId());
    while (true)
    {
        std::cout << "\n=== Game Selection ===\n";
        std::cout << "1. Play Dice Game\n";
        std::cout << "2. Play Coin Flip\n";
        std::cout << "3. Play Blackjack\n";
        std::cout << "4. Play The Slot Machine\n";
        std::cout << "5. Play our version of Russian Roulette\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        if (std::cin >> choice)
        {
            clearInputBuffer();
            switch (choice)
            {
            case 1:
                playDiceGame(session);
                break;
            case 2:
                playCoinFlipGame(session);
                break;
            case 3:
                playBlackjack(session);
                break;
            case 4:
                playSlotGame(session);
                break;
            case 5:
                playRussianRoulette(session);
                break;
            case 0:
                std::cout << "Thanks for playing!\n";
                return 0;
            default:
                std::cout << "Invalid choice!\n";
            }
        }
        else
        {
            clearInputBuffer();
            std::cout << "Invalid input! Please enter [1 - 4] or 0\n";
        }

        // Показываем баланс после каждой игры
        std::cout << "\nYour current balance: $" << player->getBalance() << "\n";
        if (player->getBalance() == 0)
        {
            break;
        }
    }

    // Show final results
    std::cout << "\n=== Game Over ===\n";
    std::cout << "Final balance: $" << casinoRound(player->getBalance()) << "\n";
    std::cout << "Thanks for playing!\n";

    return 0;
}
