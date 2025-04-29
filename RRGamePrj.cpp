#include <iostream>
#include <iomanip>
#include <limits>
#include <random>

// Function declarations
void displayRules();
bool playRound(const bool* chambers, int numChambers, int& currentChamber, int& playerScore, int& computerScore, bool isPlayerTurn);
void displayScores(int playerScore, int computerScore, int winningScore);
int getValidInput(const char* prompt, int min, int max);
void initializeGame(bool* chambers, int numChambers, int numBullets);
void displayGameState(int currentChamber, int numChambers, bool isPlayerTurn);
bool playTurn(const bool* chambers, int numChambers, int& currentChamber, int& score, bool isPlayer);
bool decideToQuit(const bool* chambers, int currentChamber, int& score);
void drawRevolver(int numChambers, int currentChamber);
void drawChamberResult(bool isBullet);

int main() {
    // Seed random number generator
    srand((unsigned)time(NULL));
    std::string play = "X";
    do{
        do{
            std::cout << "\nHello my dear little friend, want to play a game?\n";
            std::cout << "(Y)es or (N)o: ";
            std::cin >> play;
            std::cout << '\n';
            if(play != "N" && play != "Y"){
                std::cout << "Invalid Input, Try Again\n";
            }
        }while(play != "N" && play != "Y");

        if(play == "N") {
            break;  // Exit if 'N'
        }

        displayRules();
    
        // Game setup with customizable parameters
        int numChambers = getValidInput("Enter number of chambers (3-6): ", 3, 6);
        int numBullets = getValidInput("Enter number of bullets (", 1, numChambers - 1);
        int winningScore = getValidInput("Enter winning score (5-20): ", 5, 20);
    
        std::cout << "\nGame configured with " << numChambers << " chambers, " << numBullets << " bullets, and " << winningScore << " winning score.\n\n";
    
        // Initialize game state
        bool* chambers = new bool[numChambers]; // Dynamically allocate array
        initializeGame(chambers, numChambers, numBullets);
   
        std::cout << "Press Any Key and Enter to continue...";
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
        int playerScore = 0;
        int computerScore = 0;
        int currentChamber = 0;
        bool isPlayerTurn = true;
    
        // Main game loop
        while (playerScore < winningScore && computerScore < winningScore && 
            playerScore > -winningScore && computerScore > -winningScore) {
        
            std::cout << "\n----------------------------------------\n";
            displayScores(playerScore, computerScore, winningScore);
            displayGameState(currentChamber, numChambers, isPlayerTurn);
    
            bool roundContinues = playRound(chambers, numChambers, currentChamber, playerScore, computerScore, isPlayerTurn);
            if (isPlayerTurn){
                std::cout << "Press Any Key and Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else{
                std::cout << "Press Any Key and Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }

            if (playerScore >= winningScore || computerScore >= winningScore || 
                playerScore <= -winningScore || computerScore <= -winningScore) {
                break;
            }
            if (!roundContinues) {
                // Reset the game for a new round
                initializeGame(chambers, numChambers, numBullets);
                currentChamber = 0;
            }
        
            // Switch turns
            isPlayerTurn = !isPlayerTurn;
        }
    
        // Display final result
        std::cout << "\n==============================================\n";
        std::cout << "GAME OVER\n";
        if (playerScore >= winningScore || computerScore <= -winningScore) {
            std::cout << "Congratulations! You win!\n";
        } else {
            std::cout << "Sorry, the computer wins.\n";
        }
        std::cout << "Final scores:\n";
        displayScores(playerScore, computerScore, winningScore);
        std::cout << "==============================================\n";
    
        // Clean up dynamically allocated memory
        delete[] chambers;

    }while(play != "N");

    return 0;
}

// Function to display game rules
void displayRules() {
    std::cout << "========== RUSSIAN ROULETTE GAME ==========\n";
    std::cout << "Rules:\n";
    std::cout << "1. A revolver has a customizable number of chambers with some containing bullets.\n";
    std::cout << "2. You and the computer take turns pulling the trigger.\n";
    std::cout << "3. When it's your turn, you can choose to play or quit.\n";
    std::cout << "4. If you play and hit a blank, you get 1 point.\n";
    std::cout << "5. If you play and hit a bullet, you lose 1 point.\n";
    std::cout << "6. If you quit and it would have been a blank, you lose 2 points.\n";
    std::cout << "7. If you quit and it would have been a bullet, you gain 2 points.\n";
    std::cout << "8. The same scoring applies to the computer.\n";
    std::cout << "9. The game continues until someone reaches the winning score or drops below negative winning score.\n";
    std::cout << "==========================================\n\n";
}

// Function to get valid input within a range
int getValidInput(const char* prompt, int min, int max) {
    int input;
    bool validInput = false;
    
    do {
        std::cout << prompt;
        // Special case for bullet prompt that requires range
        if (std::string(prompt).find("bullets") != std::string::npos) {
            std::cout << min << "-" << max << "): ";
        }
        
        if (std::cin >> input) {
            if (input >= min && input <= max) {
                validInput = true;
            } else {
                std::cout << "Please enter a value between " << min << " and " << max << ".\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
        }
    } while (!validInput);
    
    return input;
}

// Function to initialize the game chambers
void initializeGame(bool* chambers, int numChambers, int numBullets) {
    // Reset all chambers to empty
    for (int i = 0; i < numChambers; i++) {
        chambers[i] = false;
    }
    
    // Place bullets randomly
    int bulletsPlaced = 0;
    while (bulletsPlaced < numBullets) {
        int chamber = rand() % numChambers;
        if (!chambers[chamber]) {
            chambers[chamber] = true;  // Place a bullet
            bulletsPlaced++;
        }
    }
    
    std::cout << "\nNew round started. Good luck Player #*&^*&$%^$^$%&^$$# ...\n";
}

// Function to draw the revolver visualization
void drawRevolver(int numChambers, int currentChamber) {
    std::cout << "\n";
    
    // Top part of revolver
    std::cout << "      _____        \n";
    std::cout << "    /       \\     \n";
    
    // Draw chambers in a circle
    const int maxChambersInRow = 6;
    
    if (numChambers <= maxChambersInRow) {
        // Draw chambers in a single row
        std::cout << "  |";
        for (int i = 0; i < numChambers; i++) {
            if (i == currentChamber) {
                std::cout << " *" << i + 1 << "* ";
            } else {
                std::cout << " " << i + 1 << " ";
            }
        }
        std::cout << "|\n";
    } else {
        // Top row of chambers
        std::cout << "  |";
        for (int i = 0; i < maxChambersInRow; i++) {
            if (i == currentChamber) {
                std::cout << "*" << (i + 1) << "*";
            } else {
                std::cout << " " << (i + 1) << " ";
            }
        }
        std::cout << "|\n";
        
        // Bottom row of chambers
        std::cout << "  |";
        for (int i = maxChambersInRow; i < numChambers; i++) {
            if (i == currentChamber) {
                std::cout << "*" << (i + 1) << "*";
            } else {
                std::cout << " " << (i + 1) << " ";
            }
        }
        // Fill remaining space
        for (int i = numChambers; i < maxChambersInRow * 2; i++) {
            std::cout << "   ";
        }
        std::cout << "|\n";
    }
    
    // Handle of the gun
    std::cout << "    \\       /    \n";
    std::cout << "     _______     \n";
    std::cout << "     -------      \n";
    std::cout << "       | |        \n";
    std::cout << "       | |        \n";
    std::cout << "     __| |__      \n";
    std::cout << "    /       \\    \n";
    std::cout << "\n";
}

// Function to draw the chamber result (bullet or blank)
void drawChamberResult(bool isBullet) {
    if (isBullet) {
        // Draw bullet fired
        std::cout << "\n";
        std::cout << "      BANG!      \n";
        std::cout << "       ___       \n";
        std::cout << "     /     \\     \n";
        std::cout << "     | (*) |     \n";
        std::cout << "     \\ ___ /     \n";
        std::cout << "        |        \n";
        std::cout << "      /   \\      \n";
        std::cout << "     /     \\     \n";
        std::cout << "\n";
    } else {
        // Draw empty chamber click
        std::cout << "\n";
        std::cout << "      CLICK      \n";
        std::cout << "       ___       \n";
        std::cout << "     /     \\     \n";
        std::cout << "     |  O  |     \n";
        std::cout << "     \\ ___ /     \n";
        std::cout << "                 \n";
        std::cout << "\n";
    }
}

// Function to display current game state
void displayGameState(int currentChamber, int numChambers, bool isPlayerTurn) {
    std::cout << "Current chamber: " << (currentChamber + 1) << " of " << numChambers << "\n";
    std::cout << (isPlayerTurn ? "Your turn" : "Computer's turn") << " to pull the trigger.\n";
    drawRevolver(numChambers, currentChamber);
}

// Function to display current scores
void displayScores(int playerScore, int computerScore, int winningScore) {
    std::cout << "+---------------------------+\n";
    std::cout << "| SCORES  [Target: " << std::setw(3) << winningScore << "]     |\n";
    std::cout << "| You: " << std::setw(3) << playerScore << "  | Computer: " << std::setw(3) << computerScore << " |\n";
    std::cout << "+---------------------------+\n";
}

// Function to let player decide whether to quit
bool decideToQuit(const bool* chambers, int currentChamber, int& score) {
    char decision;
    std::cout << "Do you want to (P)lay or (Q)uit this turn? ";
    
    while (true) {
        std::cin >> decision;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        decision = std::toupper(decision);
        
        if (decision == 'P') {
            return false;  // Don't quit
        } else if (decision == 'Q') {
            // Apply quit scoring
            if (chambers[currentChamber]) {  // Would have been a bullet
                score += 2;
                std::cout << "Good choice! There was a bullet in the chamber. You gain 2 points.\n";
                drawChamberResult(true);
            } else {  // Would have been a blank
                score -= 2;
                std::cout << "Bad choice! The chamber was empty. You lose 2 points.\n";
                drawChamberResult(false);
            }
            return true;  // Quit
        } else {
            std::cout << "Invalid choice. Please enter 'P' to play or 'Q' to quit: ";
        }
    }
}

// Function to handle a single turn
bool playTurn(const bool* chambers, int numChambers, int& currentChamber, int& score, bool isPlayer) {
    bool isBullet = chambers[currentChamber];
    
    if (isPlayer) {
        std::cout << "You pull the trigger... ";
    } else {
        // Simple computer AI: always plays (never quits)
        std::cout << "Computer pulls the trigger...\n";
    }
    
    if (isBullet) {
        std::cout << "BANG! There was a bullet!\n";
        drawChamberResult(true);
        score -= 1;
        if (isPlayer) {
            std::cout << "You lose 1 point.\n";
        } else {
            std::cout << "Computer loses 1 point.\n";
        }
        return false;  // End of round
    } else {
        std::cout << "Click. Empty chamber.\n";
        drawChamberResult(false);
        score += 1;
        if (isPlayer) {
            std::cout << "You gain 1 point.\n";
        } else {
            std::cout << "Computer gains 1 point.\n";
        }
        
        // Move to next chamber
        currentChamber = (currentChamber + 1) % numChambers;
        return true;  // Round continues
    }
}

// Function to play a round of the game
bool playRound(const bool* chambers, int numChambers, int& currentChamber, int& playerScore, 
               int& computerScore, bool isPlayerTurn) {
    if (isPlayerTurn) {
        // Player's turn
        bool quit = decideToQuit(chambers, currentChamber, playerScore);
        if (quit) {
            // Move to next chamber after quitting
            currentChamber = (currentChamber + 1) % numChambers;
            return true;  // Round continues
        }
        
        return playTurn(chambers, numChambers, currentChamber, playerScore, true);
    } else {
        // Computer's turn (always plays)
        return playTurn(chambers, numChambers, currentChamber, computerScore, false);
    }
}