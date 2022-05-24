#include "sudoku/format.hpp"
#include "sudoku/sudoku.hpp"

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/xchar.h>

#include <iostream>
#include <regex>
#include <string>

#if defined(_WIN32)
#include <io.h>    // for _setmode()
#include <fcntl.h> // for _O_U16TEXT
#endif

static const std::wstring instructions =
    L"help                  Print these instructions.\n"
    L"new                   Generate and start a new game.\n"
    L"[a-z][1-9] [value]    Enter a value in the grid.\n"
    L"                        Number and letter can be switched.\n"
    L"                        Value can be within interval [0,9] (0 to erase).\n"
    L"check                 Check if your answer is correct.\n"
    L"show                  Show the player again grid.\n"
    L"reset                 Reset your grid to the original question.\n"
    L"cheat                 Show the solution.\n"
    L"exit                  Exit the program.\n"
;

int main()
{
#if defined(_WIN32)
    _setmode(_fileno(stdout), _O_U8TEXT);
#endif

    std::wcout << instructions;
    std::wcout << std::endl;

    sudoku::game game;
    game.init();

    std::wcout << sudoku::format(game.question_grid());
    std::wcout << std::endl;

    std::string prompt;
    unsigned long wrong_input_count = 0;

    const std::regex regex[] = {
        std::regex("([a-i])([1-9]) ([0-9])"),
        std::regex("([1-9])([a-i]) ([0-9])")
    };

    while (true)
    {
        std::wcout << L">>> ";
        std::getline(std::cin, prompt);
        std::wcout << std::endl;

        if (prompt == "exit")
        {
            break;
        }

        if (prompt == "help")
        {
            std::wcout << instructions;
            std::wcout << std::endl;
            continue;
        }

        if (prompt == "new")
        {
            game.init();
            std::wcout << sudoku::format(game.question_grid());
            std::wcout << std::endl;
            continue;
        }

        if (prompt == "check")
        {
            std::wcout << (game.check() ? L"Correct!\n" : L"Incorrect...\n");
            std::wcout << std::endl;
            continue;
        }

        if (prompt == "show")
        {
            std::wcout << sudoku::format(game.player_grid(), game.question_grid());
            std::wcout << std::endl;
            continue;
        }

        if (prompt == "reset")
        {
            game.reset_player();
            std::wcout << sudoku::format(game.question_grid());
            std::wcout << std::endl;
            continue;
        }

        if (prompt == "cheat")
        {
            std::wcout << sudoku::format(game.solution_grid());
            std::wcout << std::endl;
            continue;
        }

        std::smatch matches;

        if (std::regex_match(prompt, matches, regex[0]))
        {
            uint8_t col = matches[1].str().c_str()[0] - 'a';
            uint8_t row = matches[2].str().c_str()[0] - '1';
            uint8_t val = matches[3].str().c_str()[0] - '0';

            sudoku::result result = game.enter_value(row, col, val);

            if (result == sudoku::result::ok)
                std::wcout << sudoku::format(game.player_grid(), game.question_grid());
            else if (result == sudoku::result::index_out_of_bounds) // regex makes this impossible
                std::wcout << L"Indices out of bounds!\n";
            else if (result == sudoku::result::value_out_of_bounds) // regex makes this impossible
                std::wcout << L"Value out of bounds!\n";
            else if (result == sudoku::result::attempted_overwrite)
                std::wcout << L"Can't modify a clue!\n";

            std::wcout << std::endl;
            continue;
        }

        if (std::regex_match(prompt, matches, regex[1]))
        {
            uint8_t row = matches[1].str().c_str()[0] - '1';
            uint8_t col = matches[2].str().c_str()[0] - 'a';
            uint8_t val = matches[3].str().c_str()[0] - '0';

            sudoku::result result = game.enter_value(row, col, val);

            if (result == sudoku::result::ok)
                std::wcout << sudoku::format(game.player_grid(), game.question_grid());
            else if (result == sudoku::result::index_out_of_bounds) // regex makes this impossible
                std::wcout << L"Indices out of bounds!\n";
            else if (result == sudoku::result::value_out_of_bounds) // regex makes this impossible
                std::wcout << L"Value out of bounds!\n";
            else if (result == sudoku::result::attempted_overwrite)
                std::wcout << L"Can't modify a clue!\n";

            std::wcout << std::endl;
            continue;
        }

        // default case, assume wrong input
        if (++wrong_input_count >= 3)
        {
            std::wcout << L"Need help with controls? Enter 'help'\n" << std::endl;
            wrong_input_count = 0;
        }
    }

    return 0;
}
