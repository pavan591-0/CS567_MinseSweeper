#include "Minesweeper.h"
#include <iostream>
#include <cstdlib>

Minesweeper::Minesweeper() {
    // Initialize the board with all cells unrevealed and unflagged
    revealed.resize(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    flagged.resize(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));

    // Initialize mines randomly
    mines.resize(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    int count = 0;
    while (count < NUM_MINES) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (!mines[row][col]) {
            mines[row][col] = true;
            count++;
        }
    }
}

void Minesweeper::initializeBoard() {
    board.assign(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '-'));
    revealed.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    flagged.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    gameOver = false;
    gameWon = false;
}

void Minesweeper::placeMines() {
    int minesPlaced = 0;
    while (minesPlaced < NUM_MINES) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (board[row][col] != '*') {
            board[row][col] = '*';
            minesPlaced++;
        }
    }
}

void Minesweeper::calculateNumbers() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] != '*') {
                int count = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int r = row + dr;
                        int c = col + dc;
                        if (isValidCell(r, c) && board[r][c] == '*') {
                            count++;
                        }
                    }
                }
                if (count > 0) {
                    board[row][col] = '0' + count;
                }
            }
        }
    }
}

bool Minesweeper::isValidCell(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

void Minesweeper::revealCellRecursive(int row, int col) {
    if (!isValidCell(row, col) || revealed[row][col]) {
        return;
    }
    revealed[row][col] = true;
    if (board[row][col] == '0') {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                revealCellRecursive(row + dr, col + dc);
            }
        }
    }
}

bool Minesweeper::checkWin() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (!revealed[row][col] && board[row][col] != '*') {
                return false;
            }
        }
    }
    return true;
}

void Minesweeper::restartGame() {
    initializeBoard();
    placeMines();
    calculateNumbers();
}

void Minesweeper::printBoard(bool revealMines) {
    std::cout << "   ";
    for (int col = 0; col < BOARD_SIZE; ++col) {
        std::cout << col << ' ';
    }
    std::cout << '\n';
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::cout << row << "  ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (revealed[row][col] || (board[row][col] == '*' && revealMines)) {
                std::cout << board[row][col] << ' ';
            } else {
                std::cout << '-' << ' ';
            }
        }
        std::cout << '\n';
    }
}

void Minesweeper::startTimer() {
    startTime = time(nullptr);
}

long long Minesweeper::getElapsedTime() {
    return time(nullptr) - startTime;
}

int Minesweeper::getBoardSize() const {
    return BOARD_SIZE;
}

bool Minesweeper::isGameOver() const {
    return gameOver;
}

bool Minesweeper::isGameWon() const {
    return gameWon;
}

void Minesweeper::revealCell(int row, int col) {
    if (board[row][col] == '*') {
        gameOver = true;
        return;
    }
    if (!revealed[row][col]) {
        revealCellRecursive(row, col);
        if (checkWin()) {
            gameWon = true;
        }
    }
}

void Minesweeper::toggleFlag(int row, int col) {
    flagged[row][col] = !flagged[row][col];
}

void Minesweeper::cheat() {
    std::cout << "Cheat Mode: Revealing Mines...\n";
    printBoard(true);
}

bool Minesweeper::isCellRevealed(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false; // Out of bounds
    }
    return revealed[row][col];
}

bool Minesweeper::isCellFlagged(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false; // Out of bounds
    }
    return flagged[row][col];
}

bool Minesweeper::isMine(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false; // Out of bounds
    }
    return mines[row][col];
}