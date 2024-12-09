#include <iostream>
#include <string>
#include <limits>
#include "Minesweeper.h"

using namespace std;

void printTime(long long seconds) {
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;

    cout << "Time taken: ";
    if (hours > 0) cout << hours << " hours ";
    if (minutes > 0) cout << minutes << " minutes ";
    cout << seconds << " seconds\n";
}

int main() {
    Minesweeper game;
    game.initializeBoard();

    cout << "Welcome to Minesweeper!\n";
    cout << "You have to reveal all cells without hitting a mine.\n\n";

    bool playAgain = true;
    while (playAgain) {
        game.restartGame();
        game.printBoard();
        game.startTimer();

        while (!game.isGameOver()) {
            // Check if game is already over before processing input
            if (game.isGameOver()) {
                break;
            }

            int row, col;
            string action;
            cout << "Enter row, column, and action (R to reveal, F to flag): ";

            // Clear input buffer and ignore characters left in the buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Read row, column, and action
            cin >> row >> col >> action;

            if (row < 0 || row >= game.getBoardSize() || col < 0 || col >= game.getBoardSize()) {
                cout << "Invalid input! Please try again.\n";
                continue;
            }

            if (action == "R" || action == "r") {
                game.revealCell(row, col);
            } else if (action == "F" || action == "f") {
                game.toggleFlag(row, col);
            } else {
                cout << "Invalid action! Please enter 'R' to reveal or 'F' to flag.\n";
                continue;
            }

            game.printBoard();

            if (game.isGameOver()) {
                if (game.isGameWon()) {
                    cout << "Congratulations! You won!\n";
                } else {
                    cout << "Game over! You hit a mine!\n";
                }
                printTime(game.getElapsedTime());
            }
        }

        cout << "Do you want to play again? (yes/no): ";
        string choice;
        cin >> choice;
        if (choice != "yes" && choice != "Yes") {
            playAgain = false;
        }
    }

    return 0;
}
