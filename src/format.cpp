#include "sudoku/format.hpp"

namespace sudoku {

static const std::wstring alpha  { L"    a b c   d e f   g h i\n"   };
static const std::wstring top    { L"  ┌───────┬───────┬───────┐\n" };
static const std::wstring middle { L"  ├───────┼───────┼───────┤\n" };
static const std::wstring bottom { L"  └───────┴───────┴───────┘\n" };

const std::wstring format(const sudoku::grid& board)
{
    std::wstring out;

    out += sudoku::alpha;
    out += sudoku::top;

    for (auto i = 0; i < 9; ++i)
    {
        out += std::to_wstring(i + 1) + L" | ";
        for (auto j = 0; j < 9; ++j)
        {
            if (board[i][j] != 0)
                out += std::to_wstring(board[i][j]);
            else
                out += L"-";

            if ((j + 1) % 3 == 0)
                out += L" |";

            out += L" ";
        }
        out += std::to_wstring(i + 1) + L"\n";

        if (((i + 1) % 3 == 0) && (i != 0 && i != 8))
            out += sudoku::middle;
    }

    out += sudoku::bottom;
    out += sudoku::alpha;

    return out;
}

const std::wstring format(const sudoku::grid& player, const sudoku::grid& question)
{
    std::wstring out;

    out += sudoku::alpha;
    out += sudoku::top;

    for (auto i = 0; i < 9; ++i)
    {
        out += std::to_wstring(i + 1) + L" | ";
        for (auto j = 0; j < 9; ++j)
        {
            if (question[i][j] != 0)
                out += std::to_wstring(question[i][j]);
            else if (player[i][j] != 0)
                out += L"\x1B[31m" + std::to_wstring(player[i][j]) + L"\x1B[0m";
            else
                out += L"-";

            if ((j + 1) % 3 == 0)
                out += L" |";

            out += L" ";
        }
        out += std::to_wstring(i + 1) + L"\n";

        if (((i + 1) % 3 == 0) && (i != 0 && i != 8))
            out += sudoku::middle;
    }

    out += sudoku::bottom;
    out += sudoku::alpha;

    return out;
}

}
