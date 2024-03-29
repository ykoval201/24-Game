//Author:  Yurii Koval
//Date:    04-14-2023
//Course:  CS211
//System:  Linux(ubuntu)
//IDE: Clion
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


//Defining the stack
struct stackNode {
    char data;
    struct stackNode *nextPtr;
};typedef struct stackNode StackNode;

struct stack {
    StackNode *topPtr;
};typedef struct stack Stack;

//Defining functions

//Stack functions
Stack *createStack();//Creates a stack
void push(Stack *sPtr, char value);//Pushes a value onto the stack
char pop(Stack *sPtr);//Pops(deletes) and returns a value off the stack
int isEmpty(Stack s);//Checks if the stack is empty
char peek(Stack s);//Peeks at the top of the stack without popping(deleting) it
void clearStack(Stack *sPtr);//deallocates the stack

//Expression evaluation functions

//Converts a user-entered expression to an expression that can be evaluated
//Is called from inside the evaluateExpression function
char *convertString(const char *infix_expression);
int evaluateExpression(const char *userAnswer);//Evaluates the expression

//Utility functions
int isOperator(char c);//Checks if a character is an operator
int isValidExpression(const char *userAnswer, char* given);//Checks if the user-entered expression is valid
int isValidSymbol(char c);//Checks if a character is a valid symbol
int isNumsUsedOnce(const char *userAnswer, const char given[]);//Checks if the user used each number exactly once

//Gameplay functions
void welcomeMessage();//Prints the welcome message
void difficultyMenu();//Prints the difficulty menu
int playRound(char *puzzle);//Plays a round of the game with the given puzzle
char* getPuzzle(const char *fileName);//Generates the numbers for the game
int afterRoundMenu();//Prints the menu after a round is finished that asks the user if they want to play again
int precedence(char op) {
    switch (op) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return -1;  // Invalid operator
    }
}



int main() {

    srand(1);

    char easyFile[] = "easy.txt";
    char mediumFile[] = "medium.txt";
    char hardFile[] = "hard.txt";

    int choice = 2;
    char* puzzle;
    char difficulty = 'E';
    int round = 1;
    welcomeMessage();

    do {
        if(choice == 2) {
            difficultyMenu();
            scanf("%c%*c", &difficulty);
        }

        switch(difficulty) {
            case 'E':
                puzzle = getPuzzle(easyFile);
                choice = playRound(puzzle);
                free(puzzle);
                if(choice != 0){
                    choice = afterRoundMenu();
                }
                break;
            case 'M':
                puzzle = getPuzzle(mediumFile);
                choice = playRound(puzzle);
                free(puzzle);
                if(choice != 0){
                    choice = afterRoundMenu();
                }
                break;
            case 'H':
                puzzle = getPuzzle(hardFile);
                choice = playRound(puzzle);
                free(puzzle);
                if(choice != 0){
                    choice = afterRoundMenu();
                }
                break;
            default:
               puzzle = getPuzzle(easyFile);
                choice = playRound(puzzle);
                free(puzzle);
                if(choice != 0){
                    choice = afterRoundMenu();
                }
                break;

        }



    } while (choice != 3);

    printf("\nThanks for playing!\n");
    printf("Exiting...\n");

    return 0;
}

//Creates a stack
Stack *createStack() {
    Stack *sPtr = malloc(sizeof(Stack));
    sPtr->topPtr = NULL;
    return sPtr;
}

//Pushes a value onto the stack
void push(Stack *sPtr, char value) {
    StackNode *newPtr = malloc(sizeof(StackNode));
    newPtr->data = value;
    newPtr->nextPtr = sPtr->topPtr;
    sPtr->topPtr = newPtr;
}

//Pops(deletes) and returns a value off the stack
char pop(Stack *sPtr) {
    if (isEmpty(*sPtr)) {
        //printf("Stack is empty.\n");
        return '\0';
    }
    else {
        StackNode *tempPtr = sPtr->topPtr;
        char value = tempPtr->data;
        sPtr->topPtr = tempPtr->nextPtr;
        free(tempPtr);
        return value;
    }
}

//Checks if the stack is empty
int isEmpty(Stack s) {
    return s.topPtr == NULL;
}

//Peeks at the top of the stack without popping(deleting) it
char peek(Stack s) {
    if (isEmpty(s)) {
        //printf("Stack is empty.\n");
        return '\0';
    }
    else {
        return s.topPtr->data;
    }
}

//deallocates the stack
void clearStack(Stack *sPtr) {
    while(!isEmpty(*sPtr)) {
        pop(sPtr);
    }

}

//Converts a user-entered expression to an expression that can be evaluated
//Is called from inside the evaluateExpression function
char* convertString(const char* infix_expression) {
    Stack* sPtr = createStack();
    char* postfix_expression = malloc(sizeof(char) * 100);
    memset(postfix_expression, '\0', sizeof(char) * 100);
    int i = 0;
    int j = 0;
    while (infix_expression[i] != '\0') {
        if (isdigit(infix_expression[i])) {
            postfix_expression[j] = infix_expression[i];
            j++;
        } else if (infix_expression[i] == '(') {
            push(sPtr, infix_expression[i]);
        } else if (infix_expression[i] == ')') {
            while (peek(*sPtr) != '(') {
                postfix_expression[j] = pop(sPtr);
                j++;
                if (j > strlen(postfix_expression)){
                    break;
                }
            }
            pop(sPtr);
        } else if (isOperator(infix_expression[i])) {
            while (!isEmpty(*sPtr) && peek(*sPtr) != '(' &&
                   precedence(infix_expression[i]) <= precedence(peek(*sPtr))) {
                postfix_expression[j] = pop(sPtr);
                j++;
            }
            push(sPtr, infix_expression[i]);
        }
        i++;
    }
    while (!isEmpty(*sPtr)) {
        postfix_expression[j] = pop(sPtr);
        j++;
    }
    postfix_expression[j] = '\0';
    clearStack(sPtr);
    free(sPtr);
    return postfix_expression;
}


//Evaluates the expression
int evaluateExpression(const char *userAnswer) {
    Stack *sPtr = createStack();
    char *postfix_expression = convertString(userAnswer);
    int i = 0;
    while (postfix_expression[i] != '\0') {
        if (isdigit(postfix_expression[i])) {
            push(sPtr, postfix_expression[i] - '0');
        }
        else if (isOperator(postfix_expression[i])) {
            int operand2 = pop(sPtr);
            int operand1 = pop(sPtr);
            switch (postfix_expression[i]) {
                case '+':
                    printf("%d + %d = %d.\n", operand1, operand2, operand1 + operand2);
                    push(sPtr, operand1 + operand2);
                    break;
                case '-':
                    printf("%d - %d = %d.\n", operand1, operand2, operand1 - operand2);
                    push(sPtr, operand1 - operand2);
                    break;
                case '*':
                    printf("%d * %d = %d.\n", operand1, operand2, operand1 * operand2);
                    push(sPtr, operand1 * operand2);
                    break;
                case '/':
                    printf("%d / %d = %d.\n", operand1, operand2, operand1 / operand2);
                    push(sPtr, operand1 / operand2);
                    break;
            }
        }
        i++;
    }
    int result = pop(sPtr);
    clearStack(sPtr);
    free(sPtr);
    free(postfix_expression);
    return result;
}

//Checks if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//Checks if the user-entered expression is valid
int isValidExpression(const char *userAnswer, char* given) {
    int i = 0;
    int numOpenParentheses = 0;
    int numCloseParentheses = 0;
    int numOperators = 0;
    int numOperands = 0;
    while (userAnswer[i] != '\0') {
        if (userAnswer[i] == '(') {
            numOpenParentheses++;
        }
        else if (userAnswer[i] == ')') {
            numCloseParentheses++;
        }
        else if (isOperator(userAnswer[i])) {
            numOperators++;
        }
        else if (isdigit(userAnswer[i])) {
            numOperands++;
        }
        else if (!isValidSymbol(userAnswer[i])) {
            printf("Error! Invalid symbol entered. Please try again.\n\n");
            return 0;
        }
        i++;
    }
    if (numOpenParentheses != numCloseParentheses) {
        if(numOpenParentheses > numCloseParentheses) {
            evaluateExpression(userAnswer);
            printf("Error! Too many opening parentheses in the expression.\n\n");
        }
        else {
            evaluateExpression(userAnswer);
            printf("Error! Too many closing parentheses in the expression.\n\n");

        }
        return 4;
    }
    if (numOperators != numOperands - 1) {
        if(numOperators > numOperands - 1) {
            printf("Error! Too many operators in the expression.\n\n");
            return 0;
        }
        else {
            evaluateExpression(userAnswer);
            printf("Error! Too many values in the expression.\n\n");
            return 4;
        }
        return 0;
    }
    if(!isNumsUsedOnce(userAnswer, given)){
        printf("Error! You must use all four numbers, and use each one only once. Please try again.\n\n");
        return 0;
    }
    return 1;
}

//Checks if a character is a valid symbol
int isValidSymbol(char c) {
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == ' ';
}

//Checks if the numbers are used only once
int isNumsUsedOnce(const char *userAnswer, const char given[]){

    int num_count[10] = {0}; // Initialize an array for counting the occurrences of each digit (0-9)
    int given_num_count[10] = {0}; // Initialize an array for counting the occurrences of each given number

    // Count the occurrences of each given number
    for (int i = 0; i < 4; i++) {
        given_num_count[given[i] - '0']++;
    }

    // Count the occurrences of each digit in the userAnswer
    for (int i = 0; userAnswer[i] != '\0'; i++) {
        if (isdigit(userAnswer[i])) {
            int digit = userAnswer[i] - '0'; // Convert the character to the corresponding integer
            num_count[digit]++; // Increment the count for this digit
        }
    }

    // Compare the counts in the userAnswer with the counts in the given numbers
    for (int i = 1; i <= 9; i++) { // Assuming the numbers in the puzzle are from 1 to 9
        if (num_count[i] != given_num_count[i]) {
            return 0; // If the count of any number doesn't match, return 0 (false)
        }
    }

    return 1; // If the counts of all numbers match, return 1 (true)

}

//displays welcome message
void welcomeMessage() {
    printf("Welcome to the game of TwentyFour Part Two!\n");
    printf("Use each of the four numbers shown exactly once, \n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
    printf("to yield the value twenty-four.\n");
}

//display difficulty menu
void difficultyMenu() {
    printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
    printf("Your choice --> ");
}

//get puzzle from file
char* getPuzzle(const char *fileName) {

    //open file
    FILE *file = fopen(fileName, "r");
    char line[256];
    int numberOfPossiblePuzzles = 0;

    //check if file exists
    if (file == NULL) {
        printf("File does not exist.\n");
        exit(1);
    }

    //read file and store each line in an array
    while (fgets(line, sizeof(line), file)) {
        numberOfPossiblePuzzles++;
    }

    char **puzzle = malloc(numberOfPossiblePuzzles * sizeof(char*));
    rewind(file);
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        puzzle[i] = malloc(strlen(line) + 1);
        strcpy(puzzle[i], line);
        i++;
    }

    int randomPuzzle = rand() % numberOfPossiblePuzzles;
    char *randomPuzzleString = malloc(strlen(puzzle[randomPuzzle]) + 1);
    strcpy(randomPuzzleString, puzzle[randomPuzzle]);

    //remove whitespaces from the puzzle
    //char* puzzle2 = malloc(strlen(randomPuzzleString) + 1);
    char puzzle2[strlen(randomPuzzleString) + 1];
    int j = 0;
    for (int i = 0; i < strlen(randomPuzzleString); i++) {
        //check that the character is a number
        if (isdigit(randomPuzzleString[i]) != 0) {
            //check that the number is not a whitespace
            if (randomPuzzleString[i] != ' ') {
                //add the number to the puzzle
                puzzle2[j] = randomPuzzleString[i];
                j++;
            }
        }
    }
    puzzle2[4] = '\0';

    free(randomPuzzleString);


    //Print the puzzle in this format: "The numbers to use are: 4, 4, 8, 8."
    printf("The numbers to use are: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", puzzle2[i]);
        if (i != 3) {
            printf(", ");
        }
    }
    printf(".\n");

    //loop through the puzzle array and free the memory
    for (int i = 0; i < numberOfPossiblePuzzles; i++) {
        free(puzzle[i]);

    }
    free(puzzle);
    //free(puzzle);
    fclose(file);

    char* puzzle3 = malloc(strlen(puzzle2) + 1);
    strcpy(puzzle3, puzzle2);
    return puzzle3;

}

//play the round with given puzzle
//Return 1 if the user wins, 0 if the user loses
int playRound(char* puzzle) {

    printf("Enter your solution: ");

    //char *userAnswer = malloc(256);
    char userAnswer[256];
    fgets(userAnswer, 256, stdin);
    userAnswer[strcspn(userAnswer, "\n")] = '\0'; // remove the newline character




    //check if the user entered a valid expression
    int isValid = isValidExpression(userAnswer, puzzle);
    if (!isValid) {
        //printf("Invalid expression.\n");
        return 0;
    }
    else if(isValid == 4){
        return 4;
    }

    //evaluate the user's expression
    int result = evaluateExpression(userAnswer);

    //Check if the user's answer is correct
    if (result == 24) {
        printf("Well done! You are a math genius.\n\n");
    } else {
        printf("Sorry. Your solution did not evaluate to 24.\n");
        return result;
    }

    return (result == 24);
}



//After round is played prompt user to play again or quit
//in this format:
/*Enter:    1 to play again,
            2 to change the difficulty level and then play again, or
            3 to exit the program.
Your choice --> */
int afterRoundMenu(){
    printf("Enter:    1 to play again,\n");
    printf("          2 to change the difficulty level and then play again, or\n");
    printf("          3 to exit the program.\n");
    printf("Your choice --> ");
    int choice;
    scanf("%d%*c", &choice);
    return choice;
}


/*** Test Input:
m
4 + 4 + 4 + 4
3 ^ 4 + 3 + 3
5 - 5 + (7 * 7))
1
8 + 4 + 8 * 1
(3 +4) (5/5)
1
(4 - 4)  (8 8)
1
((((( 1 + 3))) * (4-3)))
1
(9*2/1) + 6
3*/