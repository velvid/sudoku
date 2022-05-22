#include "sudoku.hpp"

#include "random_utility.hpp"

#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>

// checks if index within bounds
inline bool valid_index(uint8_t index)
{
    return (index >= 0 && index < 9);
}

// checks if value legal value
inline bool valid_value(uint8_t val)
{
    return (val >= 0 && val <= 9);
}

void sudoku::init()
{
    // generate solution
    fill(solution);

    // generate question by digging holes from solution
    question = solution;
    dig_holes(question); // TODO: handle return status

    // assign player grid for player to manipulate
    // this is done to preserve the original question grid
    player = question;
}

bool sudoku::check() const
{
    return player == solution;
}

sudoku::result sudoku::enter_value(uint8_t row, uint8_t col, uint8_t value)
{
    if (!valid_index(row) || !valid_index(col))
    {
        // TODO: create function to log to file, only for debug builds
        return result::index_out_of_bounds;
    }

    if (!valid_value(value))
    {
        return result::value_out_of_bounds;
    }

    if (question[row][col] != 0)
    {
        return result::attempted_overwrite;
    }

    player[row][col] = value;

    return result::ok;
}

void sudoku::reset_player()
{
    player = question;
}

const grid& sudoku::solution_grid()
{
    return solution;
}

const grid& sudoku::question_grid()
{
    return question;
}

const grid& sudoku::player_grid()
{
    return player;
}

void sudoku::clear(grid& board)
{
    std::fill(&board[0][0], &board[0][0] + sizeof(board), 0);
}

void sudoku::fill(grid& board)
{
    bool redo = true;

    while (redo)
    {
        // (re)set initial conditions
        redo = false;
        clear(board);
        bool illegal[9][9][9] = {{{ false }}}; // TODO: test performance with std::bitset

        for (auto row = 0; row < 9 && !redo; ++row)
            for (auto col = 0; col < 9 && !redo; ++col)
        {
            // populate vector of candidate numbers
            std::vector<uint8_t> candidates;
            for (uint8_t num = 1; num <= 9; ++num)
                if (!illegal[row][col][num - 1])
                    candidates.push_back(num);

            // there are no valid candidates (hit a dead end), so redo
            if (candidates.empty())
            {
                // TODO: develop backtracking method and compare performance to current
                redo = true;
                break;
            }

            // randomly select a number from candidates
            size_t r = rng::rand_int(0, candidates.size() - 1);
            uint8_t num = candidates[r];

            // assign number to board
            board[row][col] = num;

            // TODO: potentially assign row/col/box of illegal on separate threads
            // this is safe since it's non-shared memory for each index
            // the only shared index is [row][col][num - 1] (easy to skip this index)
            // we don't even need to skip, since each thread is setting to same value
            // no need to implement a mutex

            // remove number from legal numbers in row, col
            for (auto i = 0; i < 9; ++i)
            {
                illegal[row][i][num - 1] = true;
                illegal[i][col][num - 1] = true;
            }

            // remove number from legal numbers in box
            uint8_t box_i = (row / 3) * 3;
            uint8_t box_j = (col / 3) * 3;
            for (auto i = box_i; i < (box_i + 3); ++i)
                for (auto j = box_j; j < (box_j + 3); ++j)
            {
                illegal[i][j][num - 1] = true;
            }
        }
    }
}

sudoku::result sudoku::dig_holes(grid& board, uint8_t amount_to_dig)
{
    // vector of holes to dig
    std::vector<cell> holes;
    for (uint8_t row = 0; row < 9; ++row)
        for (uint8_t col = 0; col < 9; ++col)
            holes.push_back(cell(row, col));

    // randomly shuffle the order of holes to dig
    rng::shuffle(holes.begin(), holes.end());

    uint8_t holes_dug = 0;

    for (auto i = 0; i < amount_to_dig; ++i)
    {
        uint8_t row = holes[i].first;
        uint8_t col = holes[i].second;

        uint8_t num = board[row][col];

        if (num == 0)
        {
            return result::grid_incomplete;
        }

        board[row][col] = 0;

        // check if digging hole results in ambiguous solution (not sudoku)
        // a grid with 4 missing cells (or less) is guaranteed to be unambiguous,
        // so only check for ambiguity when more than 4 holes are dug
        if (i > 4 && !is_unambiguous(board))
        {
            // digging this hole won't work, so reset to original value
            board[row][col] = num;
            continue;
        }

        ++holes_dug;
    }

    if (holes_dug < amount_to_dig)
    {
        return result::not_fully_dug;
    }

    return result::ok;
}

bool sudoku::is_unambiguous(grid& board)
{
    std::vector<cell> holes;

    bool illegal[9][9][9] = {{{ false }}};

    // iterate over grid, skip holes, and find all legal numbers
    for (auto row = 0; row < 9; ++row)
        for (auto col = 0; col < 9; ++col)
    {
        uint8_t num = board[row][col];

        // hole encountered, keep track of cell and ignore iteration
        if (num == 0)
        {
            holes.push_back(cell(row, col));
            continue;
        }

        for (auto i = 0; i < 9; ++i)
        {
            illegal[row][i][num - 1] = true;
            illegal[i][col][num - 1] = true;
        }

        // remove number from legal numbers in box
        uint8_t box_i = (row / 3) * 3;
        uint8_t box_j = (col / 3) * 3;
        for (auto i = box_i; i < (box_i + 3); ++i)
            for (auto j = box_j; j < (box_j + 3); ++j)
        {
            illegal[i][j][num - 1] = true;
        }
    }

    // iterate over all holes to see if they have more than one legal value
    // if provided a valid grid, this essentially solves a sudoku grid
    for (auto hole : holes)
    {
        uint8_t row = hole.first;
        uint8_t col = hole.second;

        bool found = false;
        for (auto i = 0; i < 9; ++i)
        {
            // found another legal number, hence it's ambiguous
            if (!illegal[row][col][i] && found)
                return false;

            if (!illegal[row][col][i])
                found = true;
        }
    }

    return true;
}
