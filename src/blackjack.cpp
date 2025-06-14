 #include "blackjack.h"
#include "player.h"
#include <iostream>
#include <limits>

static void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Blackjack::Blackjack()
    : gameActive(false),
      currentBet(0.0),
      useBasicStrategy(false),
      roundsPlayed(0),
      totalWagered(0.0),
      totalWon(0.0) {
}

void Blackjack::startGame(std::shared_ptr<Player> player) {
    currentPlayer = player;
    gameActive = true;
    deck.reset();  // Reset and shuffle the deck
    std::cout << "=== Blackjack Game Started ===\n";
}

void Blackjack::playRound() {
    if (!gameActive) return;

    roundsPlayed++;
    playerCards.clear();
    dealerCards.clear();

    dealInitialCards();
    playerTurn();

    if (calculateHandValue(playerCards) <= 21) {
        dealerTurn();
        determineWinner();
    }

    gameActive = false;
}

void Blackjack::endGame() {
    std::cout << "=== Blackjack Game Ended ===\n";
}

double Blackjack::getHouseEdge() const { return 0.05; }
std::string Blackjack::getGameName() const { return "Blackjack"; }
bool Blackjack::isGameActive() const { return gameActive; }

uint64_t Blackjack::getTotalRoundsPlayed() const { return roundsPlayed; }
double Blackjack::getTotalAmountWagered() const { return totalWagered; }
double Blackjack::getTotalAmountWon() const { return totalWon; }

void Blackjack::dealInitialCards() {
    // Deal two cards to player
    playerCards.push_back(deck.drawCard());
    playerCards.push_back(deck.drawCard());
    
    // Deal two cards to dealer (one face up, one face down)
    dealerCards.push_back(deck.drawCard());
    dealerCards.push_back(deck.drawCard());

    std::cout << "\nYour cards:\n";
    displayCards(playerCards);
    std::cout << "Total: " << calculateHandValue(playerCards) << "\n\n";
    
    std::cout << "Dealer's cards:\n";
    displayCards(dealerCards, true);  // Hide first card
    std::cout << "Showing: " << calculateHandValue({dealerCards[1]}) << "\n";
}

void Blackjack::playerTurn() {
    if (useBasicStrategy) {
        // AI's turn
        while (calculateHandValue(playerCards) <= 21) {
            BasicStrategyAI::Action action = strategyAI.getAction(
                calculateHandValue(playerCards),
                getDealerUpCard(),
                isSoftHand(playerCards),
                canSplit()
            );

            if (action == BasicStrategyAI::Action::STAND) {
                std::cout << "AI decides to stand\n";
                break;
            }

            handleAIAction(action);
            
            if (calculateHandValue(playerCards) > 21) {
                std::cout << "AI busts with " << calculateHandValue(playerCards) << "!\n";
                break;
            }
        }
    } else {
        // Human player's turn
        char choice;
        do {
            std::cout << "\nYour cards:\n";
            displayCards(playerCards);
            std::cout << "Total: " << calculateHandValue(playerCards) << "\n\n";
            
            std::cout << "Do you want to (H)it, (S)tand, (D)ouble down";
            if (canSplit()) std::cout << ", s(P)lit";
            std::cout << "? ";
            
            std::cin >> choice;
            choice = toupper(choice);
            
            switch (choice) {
                case 'H': {
                    playerCards.push_back(deck.drawCard());
                    std::cout << "You drew: " << playerCards.back().toSymbol() << "\n";
                    break;
                }
                case 'D': {
                    if (canDoubleDown()) {
                        currentBet *= 2;
                        playerCards.push_back(deck.drawCard());
                        std::cout << "You doubled down and drew: " << playerCards.back().toSymbol() << "\n";
                        return;  // End turn after doubling down
                    } else {
                        std::cout << "Cannot double down!\n";
                        continue;
                    }
                }
                case 'P': {
                    if (canSplit()) {
                        // TODO: Implement splitting
                        std::cout << "Splitting not implemented yet!\n";
                        continue;
                    } else {
                        std::cout << "Cannot split!\n";
                        continue;
                    }
                }
                case 'S':
                    return;
                default:
                    std::cout << "Invalid choice!\n";
                    continue;
            }
            
            if (calculateHandValue(playerCards) > 21) {
                std::cout << "Bust! You lose.\n";
                break;
            }
        } while (choice != 'S');
    }
}

void Blackjack::handleAIAction(BasicStrategyAI::Action action) {
    switch (action) {
        case BasicStrategyAI::Action::HIT: {
            playerCards.push_back(deck.drawCard());
            std::cout << "AI hits and gets " << playerCards.back().toSymbol() << "\n";
            break;
        }
        case BasicStrategyAI::Action::DOUBLE: {
            if (canDoubleDown()) {
                currentBet *= 2;
                playerCards.push_back(deck.drawCard());
                std::cout << "AI doubles down and gets " << playerCards.back().toSymbol() << "\n";
            } else {
                playerCards.push_back(deck.drawCard());
                std::cout << "AI hits and gets " << playerCards.back().toSymbol() << "\n";
            }
            break;
        }
        case BasicStrategyAI::Action::SPLIT: {
            // TODO: Implement splitting
            std::cout << "AI would split, but hitting instead\n";
            playerCards.push_back(deck.drawCard());
            std::cout << "AI hits and gets " << playerCards.back().toSymbol() << "\n";
            break;
        }
        case BasicStrategyAI::Action::SURRENDER: {
            std::cout << "AI would surrender, but standing instead\n";
            break;
        }
        default:
            break;
    }
}

bool Blackjack::canSplit() const {
    return playerCards.size() == 2 && 
           playerCards[0].getRank() == playerCards[1].getRank();
}

bool Blackjack::canDoubleDown() const {
    return playerCards.size() == 2 && 
           calculateHandValue(playerCards) >= 9 && 
           calculateHandValue(playerCards) <= 11;
}

int Blackjack::getDealerUpCard() const {
    return dealerCards[1].getValue();
}

void Blackjack::dealerTurn() {
    std::cout << "\nDealer's turn:\n";
    displayCards(dealerCards);
    std::cout << "Total: " << calculateHandValue(dealerCards) << "\n";
    
    while (calculateHandValue(dealerCards) < 17) {
        dealerCards.push_back(deck.drawCard());
        std::cout << "Dealer draws: " << dealerCards.back().toSymbol() << "\n";
        std::cout << "New total: " << calculateHandValue(dealerCards) << "\n";
    }
}

void Blackjack::determineWinner() {
    int playerValue = calculateHandValue(playerCards);
    int dealerValue = calculateHandValue(dealerCards);
    
    std::cout << "\nFinal scores:\n";
    std::cout << "Your cards:\n";
    displayCards(playerCards);
    std::cout << "Your total: " << playerValue << "\n\n";
    
    std::cout << "Dealer's cards:\n";
    displayCards(dealerCards);
    std::cout << "Dealer's total: " << dealerValue << "\n\n";

    if (playerValue > 21) {
        std::cout << "You busted! Dealer wins.\n";
        currentPlayer->withdraw(currentBet);
        totalWon -= currentBet;
    } else if (dealerValue > 21) {
        std::cout << "Dealer busted! You win!\n";
        currentPlayer->deposit(currentBet * 1.5);  // Blackjack pays 3:2
        totalWon += currentBet * 1.5;
    } else if (playerValue > dealerValue) {
        std::cout << "You win!\n";
        currentPlayer->deposit(currentBet);
        totalWon += currentBet;
    } else if (playerValue < dealerValue) {
        std::cout << "Dealer wins.\n";
        currentPlayer->withdraw(currentBet);
        totalWon -= currentBet;
    } else {
        std::cout << "It's a tie!\n";
    }
}

int Blackjack::calculateHandValue(const std::vector<Card>& cards) const {
    int value = 0;
    int numAces = 0;
    
    for (const Card& card : cards) {
        if (card.getRank() == Rank::ACE) {
            numAces++;
            value += 11;
        } else {
            value += card.getValue();
        }
    }
    
    // Adjust for aces if needed
    while (value > 21 && numAces > 0) {
        value -= 10;  // Convert an ace from 11 to 1
        numAces--;
    }
    
    return value;
}

bool Blackjack::isSoftHand(const std::vector<Card>& cards) const {
    int value = 0;
    int numAces = 0;
    
    for (const Card& card : cards) {
        if (card.getRank() == Rank::ACE) {
            numAces++;
            value += 11;
        } else {
            value += card.getValue();
        }
    }
    
    return numAces > 0 && value <= 21;
}

void Blackjack::displayCards(const std::vector<Card>& cards, bool hideFirst) const {
    for (size_t i = 0; i < cards.size(); ++i) {
        if (i == 0 && hideFirst) {
            std::cout << "[Hidden] ";
        } else {
            std::cout << cards[i].toSymbol() << " ";
        }
    }
    std::cout << "\n";
}

RoundResult Blackjack::playRoundWithResult() {
    if (!gameActive) return RoundResult::EXIT;

    // Get bet amount
    double betAmount;
    while (true) {
        std::cout << "Enter bet amount (0 to quit): $";
        if (std::cin >> betAmount) {
            if (betAmount == 0) {
                return RoundResult::EXIT;
            }
            if (betAmount > 0 && betAmount <= currentPlayer->getBalance()) {
                currentBet = betAmount;
                totalWagered += betAmount;
                break;
            }
        }
        std::cout << "Invalid amount! Please enter between 0 and " 
                  << currentPlayer->getBalance() << "\n";
        clearInputBuffer();
    }

    playRound();
    return determineWinnerWithResult();
}

RoundResult Blackjack::determineWinnerWithResult() {
    int playerValue = calculateHandValue(playerCards);
    int dealerValue = calculateHandValue(dealerCards);

    if (playerValue > 21) {
        return RoundResult::LOSS;
    } else if (dealerValue > 21) {
        return RoundResult::WIN;
    } else if (playerValue > dealerValue) {
        return RoundResult::WIN;
    } else if (playerValue < dealerValue) {
        return RoundResult::LOSS;
    } else {
        return RoundResult::DRAW;
    }
}