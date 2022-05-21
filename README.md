# Sudoku

Sudoku implemented in C++. The front-end and back-end are decoupled to allow developers to implement their own front-end interface (using [`sudoku.hpp`](/inc/sudoku.hpp)) should they wish. At the moment, [`main.cpp`](src/main.cpp) file is using an optional [`print_utility.hpp`](inc/print_utility.hpp) to drive console output as a front-end interface.

You have to compile the executable yourself.

## How to play

```text
help                  Print these instructions.
new                   Generate and start a new game.
[a-z][1-9] [value]    Enter a value in the grid.
                      Number and letter can be switched.
                      Value can be within interval [0,9] (0 to erase).
check                 Check if your answer is correct.
show                  Show the original question grid.
reset                 Reset your grid to the original question.
cheat                 Show the solution.
exit                  Exit the program.
```

## Sample gameplay

Prints sudoku grid to console, and user can interact via textual inputs.

```text
>>> new

    a b c   d e f   g h i
  ┌───────┬───────┬───────┐
1 | 1 3 - | 4 7 - | 8 6 - | 1
2 | 4 9 - | 8 1 - | 2 5 - | 2
3 | - - 7 | 5 9 6 | 3 4 - | 3
  ├───────┼───────┼───────┤
4 | 8 - 9 | 7 5 4 | 6 3 2 | 4
5 | 3 5 2 | - - 9 | - - 4 | 5
6 | - 6 - | - 3 1 | 5 - 8 | 6
  ├───────┼───────┼───────┤
7 | - - 8 | 1 - 5 | 9 7 - | 7
8 | 9 7 1 | 3 6 - | - 2 5 | 8
9 | 5 2 - | - 4 7 | 1 - 6 | 9
  └───────┴───────┴───────┘
    a b c   d e f   g h i

>>> cheat

    a b c   d e f   g h i
  ┌───────┬───────┬───────┐
1 | 1 3 5 | 4 7 2 | 8 6 9 | 1
2 | 4 9 6 | 8 1 3 | 2 5 7 | 2
3 | 2 8 7 | 5 9 6 | 3 4 1 | 3
  ├───────┼───────┼───────┤
4 | 8 1 9 | 7 5 4 | 6 3 2 | 4
5 | 3 5 2 | 6 8 9 | 7 1 4 | 5
6 | 7 6 4 | 2 3 1 | 5 9 8 | 6
  ├───────┼───────┼───────┤
7 | 6 4 8 | 1 2 5 | 9 7 3 | 7
8 | 9 7 1 | 3 6 8 | 4 2 5 | 8
9 | 5 2 3 | 9 4 7 | 1 8 6 | 9
  └───────┴───────┴───────┘
    a b c   d e f   g h i
```

## TODO

- Re-implement [`print_utility.hpp`](inc/print_utility.hpp) to be portable print using [fmt](https://github.com/fmtlib/fmt) library.
- Performance optimization using multi-threading and bitsets instead of boolean arrays.
- Implement proper backtracking algorithm when hitting a dead-end when generating a grid.
- In `sudoku::init()` function, handle cases when specified number of holes aren't dug, or if grid is improperly generated.
- Proper logging for debug builds.
- Provide release builds with executables.
