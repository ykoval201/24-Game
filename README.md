Overview

This C program is a console-based game that challenges players to use basic mathematical operations (+, -, *, /) to combine four numbers and achieve a result of 24. The game is designed to be both educational and entertaining, aiming to improve the player's mental arithmetic skills. The program features different difficulty levels, a stack-based expression evaluator, and the ability to check the validity of user input.
How to Play

Upon starting the game, players are greeted with a welcome message and a prompt to choose a difficulty level (Easy, Medium, or Hard). The game then presents the player with four numbers. The player's task is to use each of these numbers exactly once, along with any combination of the four basic mathematical operations, to create an expression that evaluates to 24.

For example, given the numbers 4, 4, 8, 8, a valid solution could be (8 / (4 - (8 / 4))).

After submitting a solution, the game evaluates the expression. If the result is 24, the player wins the round; otherwise, they are prompted to try again or change the difficulty level.
Key Features

    Stack-Based Expression Evaluation: The program uses stacks to convert user-entered infix expressions to postfix notation and then evaluates them. This approach simplifies the handling of operator precedence and parentheses.
    Difficulty Levels: The game can load puzzles from different files based on the selected difficulty level, making it accessible to players of various skill levels.
    Input Validation: The program checks if the player's input is a valid expression and if each of the provided numbers is used exactly once.
    Replayability: After each round, players can choose to play again, change the difficulty level, or exit the program.
