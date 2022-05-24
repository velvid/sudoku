#pragma once

#include <array>
#include <cstdint>

namespace sudoku
{

enum class result : uint8_t
{
    ok = 0,
    uninitialised_grid,
    index_out_of_bounds,
    value_out_of_bounds,
    attempted_overwrite,
    grid_incomplete,
    not_fully_dug,
    // timed_out,
    // out_of_memory,
};

using cell = std::pair<uint8_t, uint8_t>;
using grid = std::array<std::array<uint8_t, 9>, 9>;

} // namespace sudoku
