#include "sudoku/format.hpp"
#include "sudoku/sudoku.hpp"

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
    L"                      Number and letter can be switched.\n"
    L"                      Value can be within interval [0,9] (0 to erase).\n"
    L"check                 Check if answer is correct.\n"
    L"show                  Show the player grid again.\n"
    L"reset                 Remove all player-inputted cells.\n"
    L"cheat                 Show the solution.\n"
    L"exit                  Exit the program.\n"
;

int main()
{
#if defined(_WIN32)
    _setmode(_fileno(stdout), _O_U8TEXT);
#endif

    std::wcout << instructions << L"\n";

    sudoku::game game;

    game.init();
    std::wcout << sudoku::format(game.question_grid()) << L"\n";

    std::string input;
    unsigned long wrong_input_count = 0;

    while (true)
    {
        std::wcout << L">>> ";
        std::getline(std::cin, input);
        std::wcout << L"\n";

        if (input == "exit")
        {
            break;
        }

        if (input == "help")
        {
            std::wcout << instructions << L"\n";
            continue;
        }

        if (input == "new")
        {
            game.init();
            std::wcout << sudoku::format(game.question_grid()) << L"\n";
            continue;
        }

        if (input == "check")
        {
            std::wcout << (game.check() ? L"Correct!\n" : L"Incorrect...\n") << L"\n";
            continue;
        }

        if (input == "show")
        {
            std::wcout << sudoku::format(game.player_grid(), game.question_grid()) << L"\n";
            continue;
        }

        if (input == "reset")
        {
            game.reset_player();
            std::wcout << sudoku::format(game.question_grid()) << L"\n";
            continue;
        }

        if (input == "cheat")
        {
            std::wcout << sudoku::format(game.solution_grid()) << L"\n";
            continue;
        }

        // perform a regex to parse command for grid input
        std::smatch matches;

        uint8_t col;
        uint8_t row;
        uint8_t val;

        if (std::regex_match(input, matches,std::regex{"([a-i])([1-9]) ([0-9])"}))
        {
            col = matches[1].str().c_str()[0] - 'a';
            row = matches[2].str().c_str()[0] - '1';
            val = matches[3].str().c_str()[0] - '0';
        }
        else if (std::regex_match(input, matches, std::regex{"([1-9])([a-i]) ([0-9])"}))
        {
            row = matches[1].str().c_str()[0] - '1';
            col = matches[2].str().c_str()[0] - 'a';
            val = matches[3].str().c_str()[0] - '0';
        }

        if (!matches.empty())
        {
            sudoku::result result = game.enter_value(row, col, val);

            if (result == sudoku::result::ok)
                std::wcout << sudoku::format(game.player_grid(), game.question_grid());
            else if (result == sudoku::result::index_out_of_bounds) // regex makes this impossible
                std::wcout << L"Indices out of bounds!\n";
            else if (result == sudoku::result::value_out_of_bounds) // regex makes this impossible
                std::wcout << L"Value out of bounds!\n";
            else if (result == sudoku::result::attempted_overwrite)
                std::wcout << L"Can't modify a clue!\n";

            std::wcout << L"\n";
            continue;
        }

        // default case, assume wrong input
        if (++wrong_input_count >= 3)
        {
            std::wcout << L"Need help with controls? Enter 'help'\n\n";
            wrong_input_count = 0;
        }
    }

    return 0;
}
