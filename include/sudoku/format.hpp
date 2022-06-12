// This is an optional file to aid printing. You can define your own interface
// to interface with functions from "/include/sudoku.hpp".

#pragma once

#include "shared_defs.hpp"

#include <iostream>
#include <string>

namespace sudoku {

// Formatting for a sudoku grid with box-drawing characters.
// Returns wide string due to unicode characters.
const std::wstring format(const sudoku::grid& board);

// Formatting for a sudoku grid with box-drawing characters.
// Returns wide string of formatted grid.
// Player input is coloured, clues in question grid remain uncoloured.
const std::wstring format(const sudoku::grid& player, const sudoku::grid& question);

};
