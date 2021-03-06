#pragma once

#include "shared_defs.hpp"

namespace sudoku {

class game
{
public:
    game() = default;
    ~game() = default;

    // Initialisees all the grids.
    // Solution is generated, question is generated by digging holes, and player grid is assigned.
    void init();

    // Check if player grid is equal to solution grid.
    // Returns true if equal, false if not equal.
    bool check() const;

    // Updates specified row/col value in the player grid.
    // Returns true if legal input, false if invalid.
    result enter_value(uint8_t row, uint8_t col, uint8_t value);

    // Resets player grid to question grid.
    void reset_player();

    // Returns const reference to the solution grid.
    const grid& solution_grid();

    // Returns const reference to the question grid.
    const grid& question_grid();

    // Returns const reference to the player grid.
    const grid& player_grid();

private:
    // Clear all elements of grid to 0.
    void clear(grid& board);

    // Fills the grid with random numbers within interval [1,9].
    // Guaranteed for each row, column, and box to contain unique numbers.
    void fill(grid& board);

    // Dig holes from a filled grid.
    // A hole is "dug" by setting cell to 0.
    // Holes are dug while guaranteeing non ambiguous solutions.
    result dig_holes(grid& board, uint8_t amount_to_dig = 64);

    // Takes sparsely filled grid and determines if it has unambiguous solution.
    // A solution is ambiguous if a missing cell ("hole") can take more than one value.
    // Returns true if unambiguous, false otherwise.
    bool is_unambiguous(grid& board);

private:
    grid solution {}; // stores the solution
    grid question {}; // stores the question (with missing cells from solution)
    grid player {}; // copy of the question for player to manipulate
};

}
