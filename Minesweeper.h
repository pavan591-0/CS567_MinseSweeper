#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <ctime>
#include <cstdlib>

class Minesweeper {
private:
    const int BOARD_SIZE = 8;
    const int NUM_MINES = 10;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> flagged;
    std::vector<std::vector<bool>> mines;
    bool gameOver;
    bool gameWon;
    long long startTime;

    void placeMines();
    void calculateNumbers();
    bool isValidCell(int row, int col);
    void revealCellRecursive(int row, int col);
    bool checkWin();

public:
    Minesweeper();
    void initializeBoard();
    void restartGame();
    void printBoard(bool revealMines = false);
    void startTimer();
    long long getElapsedTime();
    int getBoardSize() const;
    bool isGameOver() const;
    bool isGameWon() const;
    void revealCell(int row, int col);
    void toggleFlag(int row, int col);
    void cheat();
    bool isCellRevealed(int row, int col) const;
    bool isCellFlagged(int row, int col) const;
    bool isMine(int row, int col) const;
};

#endif /* MINESWEEPER_H */
