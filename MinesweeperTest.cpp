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
