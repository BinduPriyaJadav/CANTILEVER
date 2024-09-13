// PROJECT3-NUMBER GUESSING GAME
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <limits>   // For numeric_limits
using namespace std;

// Function to play the guessing game
void playGame(int attempts, int secretNumber, int &score, int &highScore) {
    int playerChoice;
    int hintsUsed = 0;

    // Main loop for guessing
    while (attempts > 0) {
        cout << "\nEnter your guess: ";
        while (!(cin >> playerChoice)) {
            cout << "Invalid input! Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (playerChoice == secretNumber) {
            cout << "Congratulations! You guessed the secret number " << playerChoice << " correctly!" << endl;
            score += attempts * 10; // Scoring based on remaining attempts
            if (score > highScore) {
                highScore = score;
                cout << "New High Score: " << highScore << " points!" << endl;
            }
            cout << "Your current score is: " << score << " points." << endl;
            cout << "Thanks for playing. Play again soon!" << endl;
            return;
        } else {
            cout << "Nope, " << playerChoice << " is not the right number." << endl;
            if (playerChoice > secretNumber) {
                cout << "Hint: The secret number is smaller." << endl;
            } else {
                cout << "Hint: The secret number is greater." << endl;
            }
            attempts--;
            cout << attempts << " attempts left." << endl;

            // Offer a hint if available
            if (attempts > 1 && hintsUsed < 1) {
                char useHint;
                cout << "Would you like to use a hint? (Y/N): ";
                cin >> useHint;
                if (toupper(useHint) == 'Y') {
                    hintsUsed++;
                    cout << "Hint: The secret number is between " << max(1, secretNumber - 10) << " and " 
                         << min(100, secretNumber + 10) << "." << endl;
                }
            }
        }
    }

    cout << "You couldn't guess the secret number. It was " << secretNumber << ". You lose!" << endl;
    cout << "Your score is: " << score << " points." << endl;
    cout << "Play again to improve your score!" << endl;
}

// Function to start the game with the chosen difficulty
void startGame(int difficultyChoice, int &score, int &highScore) {
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = 1 + (rand() % 100); // Generate secret number between 1 and 100

    switch (difficultyChoice) {
        case 1:
            cout << "\nEasy level: You have 10 attempts to guess the secret number." << endl;
            playGame(10, secretNumber, score, highScore);
            break;
        case 2:
            cout << "\nMedium level: You have 7 attempts to guess the secret number." << endl;
            playGame(7, secretNumber, score, highScore);
            break;
        case 3:
            cout << "\nDifficult level: You have 5 attempts to guess the secret number." << endl;
            playGame(5, secretNumber, score, highScore);
            break;
        default:
            cout << "Invalid choice. Please select a valid difficulty level." << endl;
    }
}

// Function to display the main menu and handle user input
void mainMenu() {
    int score = 0;
    int highScore = 0;
    string playerName;

    // Get player's name
    cout << "\nEnter your name: ";
    cin >> playerName;

    cout << "\n\t\t\tWelcome to GuessTheNumber Game, " << playerName << "!" << endl;
    cout << "Guess the number between 1 and 100. You will have limited attempts based on the difficulty level you choose. Good luck!" << endl;

    while (true) {
        cout << "\nChoose the difficulty level:" << endl;
        cout << "1. Easy (10 attempts)" << endl;
        cout << "2. Medium (7 attempts)" << endl;
        cout << "3. Difficult (5 attempts)" << endl;
        cout << "0. Exit" << endl;

        int difficultyChoice;
        cout << "Enter your choice: ";
        while (!(cin >> difficultyChoice)) {
            cout << "Invalid input! Please enter a number between 0 and 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (difficultyChoice == 0) {
            cout << "Thanks for playing, " << playerName << "! Your final score is: " << score << " points." << endl;
            cout << "Highest score achieved: " << highScore << " points." << endl;
            cout << "Goodbye!" << endl;
            break;
        } else {
            startGame(difficultyChoice, score, highScore);
        }

        // Offer replay option
        char replay;
        cout << "Do you want to play again? (Y/N): ";
        cin >> replay;
        if (toupper(replay) != 'Y') {
            cout << "Thanks for playing! See you next time!" << endl;
            break;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
