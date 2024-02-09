+++
# C Program for a Mathematical Puzzle Game: Achieve 24

## Overview
This C program is designed as a console-based game that challenges players to apply basic mathematical operations (+, -, *, /) to combine four numbers and reach the target number of 24. The game aims to be both educational and entertaining, enhancing the player's mental arithmetic capabilities. It incorporates various difficulty levels, employs a stack-based approach for expression evaluation, and ensures user input is valid.

## How to Play

- **Starting the Game**: Upon launch, the game welcomes players and asks them to select a difficulty level: Easy, Medium, or Hard.
- **Gameplay**: Four numbers are presented to the player. The objective is to use each number exactly once, along with any combination of the four basic operations, to form an expression that equals 24.
    - *Example*: For the numbers 4, 4, 8, 8, a possible solution is `(8 / (4 - (8 / 4)))`.
- **Evaluation**: After the player submits their solution, the game evaluates the expression. A correct solution (evaluating to 24) wins the round; otherwise, the player is encouraged to try again or adjust the difficulty.

## Key Features

- **Stack-Based Expression Evaluation**: Utilizes stacks to convert infix expressions input by the user into postfix notation for evaluation, facilitating the handling of operator precedence and parentheses.
- **Difficulty Levels**: Offers puzzles of varying complexity, sourced from different files based on the chosen difficulty level, catering to a wide range of skill levels.
- **Input Validation**: Checks for the validity of the player's expression and ensures each provided number is used exactly once.
- **Replayability**: Players have the option to replay, switch difficulty levels, or exit after each round.

## Concepts Used

- **Dynamic Memory Allocation**: Demonstrates the use of `malloc` and `free` for allocating and deallocating memory for stacks, nodes, and puzzle data dynamically.
- **Data Structures**: Implements a custom stack data structure essential for the conversion and evaluation of mathematical expressions.
- **File I/O**: Incorporates basic file input/output operations to read puzzles from text files, highlighting file handling techniques.
- **String Manipulation**: Features functions for processing and validating strings, particularly user input expressions, emphasizing string handling capabilities.

This program is a comprehensive application of C programming concepts, including dynamic memory management, data structures, file I/O, and string manipulation, packaged within an interactive and educational game framework.
+++
