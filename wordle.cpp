#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <algorithm>

using namespace std;

// List of possible words
const vector<string> WORD_LIST = {"apple", "grape", "pearl", "chess", "tiger", "melon", "horse", "zebra", "bread", "flute", "Glass", 
    "Flame", "Stone", "Broom", "Chair", "Table", "Brush", "Crown", "River", "Storm", "Mount", "Tower", "Flour", "Brick", "Plume", "Blade", 
    "Spice", "Vivid", "Chalk", "Globe", "Crane", "Tonic", "Grain", "Wheat", "Lemon", "Bison", "Moose", "Eagle", "Frost", "Bloom", "Jolly", 
    "Quirk", "Blaze", "Swarm", "Patch", "Tunic", "Mirth", "Swoop", "Flint", "Hazel", "Ridge", "Dunes", "Shore", "Winds", "Cliff", "Hatch", 
    "Bells", "Spear", "Lodge", "Fable"};

// Selects a random word from the list
string selectWord()
{
    srand(time(0));
    return WORD_LIST[rand() % WORD_LIST.size()];
}

// Prints game instructions
void printInstructions()
{
    cout << "\033[1;36mWelcome to Wordle!\033[0m\n";
    cout << "Guess the secret 5-letter word within 5 attempts.\n";
    cout << "\n";
    cout << "Color meanings:\n";
    cout << "  \033[1;32m Green\033[0m  - Correct letter in the right position\n";
    cout << "  \033[1;33m Yellow\033[0m - Correct letter in the wrong position\n";
    cout << "  \033[0;37m White\033[0m  - Incorrect letter\n";
    cout << "------------------------------------------------\n";
}

// Gives feedback on the guessed word
void printFeedback(const string &guess, const string &secret)
{
    unordered_set<char> secretLetters(secret.begin(), secret.end());

    for (int i = 0; i < 5; i++)
    {
        if (guess[i] == secret[i])
        {
            cout << "\033[1;32m" << guess[i] << " "; // Green (Correct position)
        }
        else if (secretLetters.count(guess[i]))
        {
            cout << "\033[1;33m" << guess[i] << " "; // Yellow (Wrong position)
        }
        else
        {
            cout << "\033[0;37m" << guess[i] << " "; // White (Incorrect letter)
        }
    }
    cout << "\033[0m" << endl; // Reset color
}

// Checks if a word is in the predefined word list
bool isValidWord(const string &word)
{
    return find(WORD_LIST.begin(), WORD_LIST.end(), word) != WORD_LIST.end();
}

// Main game function
void playWordle()
{
    string secretWord = selectWord();
    int attempts = 5;

    printInstructions();

    while (attempts > 0)
    {
        string guess;
        cout << "Enter your guess: ";
        cin >> guess;

        transform(guess.begin(), guess.end(), guess.begin(), ::tolower); // Convert to lowercase

        // Even if the word is invalid, count it as an attempt
        if (guess.length() != 5)
        {
            cout << "\033[1;31mInvalid input! Your guess must be exactly 5 letters.\033[0m\n";
        }
        else if (!isValidWord(guess))
        {
            cout << "\033[1;31mWarning: This word is not in the list, try with some other guess.\033[0m\n";
        }
        else
        {
            printFeedback(guess, secretWord);
        }

        // Check if the player guessed correctly
        if (guess == secretWord)
        {
            cout << "\033[1;32m Congratulations! You guessed the word correctly! \033[0m\n";
            return;
        }

        attempts--;
        cout << "Attempts left: " << attempts << "\n";
    }

    // If the player runs out of attempts
    cout << "\033[1;31mGame Over! The correct word was: " << secretWord << "\033[0m\n";
}

int main()
{
    playWordle();
    return 0;
}
