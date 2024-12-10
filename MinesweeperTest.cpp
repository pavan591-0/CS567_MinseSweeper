#include <deepstate/DeepState.hpp>
#include "Minesweeper.h"

using namespace deepstate;

TEST(Minesweeper, RevealCell_Valid) {
    // Initialize Minesweeper game
    Minesweeper game;
    game.initializeBoard();

    // Generate random row and column within the board size
    int row = DeepState_IntInRange(0, game.getBoardSize() - 1);
    int col = DeepState_IntInRange(0, game.getBoardSize() - 1);

    // Reveal a cell at the generated row and column
    game.revealCell(row, col);

    // Check if the cell is revealed
    ASSERT_TRUE(game.isCellRevealed(row, col));
}

TEST(Minesweeper, RevealCell_Invalid) {
    // Initialize Minesweeper game
    Minesweeper game;
    game.initializeBoard();

    // Test invalid cells (out of bounds)
    ASSERT_FALSE(game.isCellRevealed(-1, -1)); // Out of bounds
    ASSERT_FALSE(game.isCellRevealed(game.getBoardSize(), game.getBoardSize())); // Out of bounds

    // Attempt to reveal an invalid cell
    game.revealCell(-1, -1);
    game.revealCell(game.getBoardSize(), game.getBoardSize());

    // No cells should be revealed after invalid attempts
    ASSERT_FALSE(game.isCellRevealed(-1, -1));
    ASSERT_FALSE(game.isCellRevealed(game.getBoardSize(), game.getBoardSize()));
}


TEST(Minesweeper, FlagAndUnflagCell) {
    // Initialize Minesweeper game
    Minesweeper game;
    game.initializeBoard();

    int row = 1;
    int col = 1;

    // Test flagging a cell
    game.toggleFlag(row, col);
    ASSERT_TRUE(game.isCellFlagged(row, col));

    // Test unflagging the cell
    game.toggleFlag(row, col);
    ASSERT_FALSE(game.isCellFlagged(row, col));
}

TEST(Minesweeper, RestartGame) {
    // Initialize Minesweeper game
    Minesweeper game;
    game.initializeBoard();

    // Reveal a cell
    game.revealCell(0, 0);
    ASSERT_TRUE(game.isCellRevealed(0, 0));

    // Restart the game
    game.restartGame();

    // Check if the board is reset
    ASSERT_FALSE(game.isCellRevealed(0, 0));  // The cell should be unrevealed after restart
}

TEST(Minesweeper, GetElapsedTime) {
    // Initialize Minesweeper game
    Minesweeper game;
    game.startTimer();

    // Wait for some time and check elapsed time
    long long elapsed = game.getElapsedTime();
    ASSERT_TRUE(elapsed >= 0);  // Ensure that elapsed time is a non-negative value
}

