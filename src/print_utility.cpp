#include "print_utility.hpp"

namespace draw
{
    static std::wstring row(const uint8_t index, const std::array<uint8_t, 9>& numbers)
    {
        std::wstring ret {};

        ret += std::to_wstring(index + 1) + L" | ";

        for (auto i = 0; i < 9; ++i)
        {
            if (numbers[i] != 0)
                ret += std::to_wstring(numbers[i]);
            else
                ret += L"-";

            if ((i + 1) % 3 == 0)
                ret += L" |";

            ret += L" ";
        }

        ret += std::to_wstring(index + 1) + L"\n";

        return ret;
    }
}

std::wostream& operator<<(std::wostream& out, const grid& board)
{
    out <<  draw::alpha;
    out <<  draw::top;

    for (auto i = 0; i < 9; ++i)
    {
        out <<  draw::row(i, board[i]);

        if (((i + 1) % 3 == 0) && (i != 0 && i != 8))
            out <<  draw::middle;
    }

    out <<  draw::bottom;
    out <<  draw::alpha;

    return out;
}
