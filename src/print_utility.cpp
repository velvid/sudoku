#include "print_utility.hpp"

namespace draw::narrow
{
    static std::string row(const uint8_t index, const std::array<uint8_t, 9>& numbers)
    {
        std::string ret {};

        ret += std::to_string(index + 1) + " | ";

        for (auto i = 0; i < 9; ++i)
        {
            ret += ((numbers[i] != 0) ? std::to_string(numbers[i]) : "-");

            if ((i + 1) % 3 == 0)
                ret += " |";

            ret += " ";
        }

        ret += std::to_string(index + 1) + "\n";

        return ret;
    }
}

std::ostream& operator<<(std::ostream& out, const grid& board)
{
    out <<  draw::narrow::alpha;
    out <<  draw::narrow::middle;

    for (auto i = 0; i < 9; ++i)
    {
        out <<  draw::narrow::row(i, board[i]);

        if (((i + 1) % 3 == 0) && (i != 0 && i != 8))
            out <<  draw::narrow::middle;
    }

    out <<  draw::narrow::middle;
    out <<  draw::narrow::alpha;

    return out;
}

namespace draw::wide
{
    static std::wstring row(const uint8_t index, const std::array<uint8_t, 9>& numbers)
    {
        std::wstring ret {};

        ret += std::to_wstring(index + 1) + L" | ";

        for (auto i = 0; i < 9; ++i)
        {
            ret += ((numbers[i] != 0) ? std::to_wstring(numbers[i]) : L"-");

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
    out <<  draw::wide::alpha;
    out <<  draw::wide::top;

    for (auto i = 0; i < 9; ++i)
    {
        out <<  draw::wide::row(i, board[i]);

        if (((i + 1) % 3 == 0) && (i != 0 && i != 8))
            out <<  draw::wide::middle;
    }

    out <<  draw::wide::bottom;
    out <<  draw::wide::alpha;

    return out;
}
