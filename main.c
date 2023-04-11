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
int isValidExpression(const char *userAnswer, int given[4]);//Checks if the user-entered expression is valid
int isValidSymbol(char c);//Checks if a character is a valid symbol
int isNumsUsedOnce(const char *userAnswer, const int given[4]);//Checks if the user used each number exactly once

//Gameplay functions
void welcomeMessage();//Prints the welcome message
void difficultyMenu();//Prints the difficulty menu
int playRound(int* puzzle);//Plays a round of the game with the given puzzle
int* getPuzzle(const char *fileName);//Generates the numbers for the game
int afterRoundMenu();//Prints the menu after a round is finished that asks the user if they want to play again



int main() {

    srand(1);

    char easyFile[] = "easy.txt";
    char mediumFile[] = "medium.txt";
    char hardFile[] = "hard.txt";

    int choice;
    char difficulty = 'E';

    do {
        welcomeMessage();
        difficultyMenu();
        scanf(" %c", &difficulty);
        getchar(); // Consume the newline character after the scanf

        switch(difficulty) {
            case 'E':
                choice = playRound(getPuzzle(easyFile));
                break;
            case 'M':
                choice = playRound(getPuzzle(mediumFile));
                break;
            case 'H':
                choice = playRound(getPuzzle(hardFile));
                break;
            default:
                printf("Invalid choice, defaulting to easy difficulty.\n");
                choice = playRound(getPuzzle(easyFile));
                break;
        }

        if (choice == 1) {
            continue;
        } else if (choice == 0) {
            choice = afterRoundMenu();
        }

    } while (choice == 1 || choice == 2);

    printf("Thank you for playing! Goodbye!\n");

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
        printf("Stack is empty.\n");
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
        printf("Stack is empty.\n");
        return '\0';
    }
    else {
        return s.topPtr->data;
    }
}

//deallocates the stack
void clearStack(Stack *sPtr) {
    if (isEmpty(*sPtr)) {
        printf("Stack is empty.\n");
    }
    else {
        StackNode *tempPtr;
        while (sPtr->topPtr != NULL) {
            tempPtr = sPtr->topPtr;
            sPtr->topPtr = tempPtr->nextPtr;
            free(tempPtr);
        }
    }
}

//Converts a user-entered expression to an expression that can be evaluated
//Is called from inside the evaluateExpression function
char *convertString(const char *infix_expression) {
    Stack *sPtr = createStack();
    char *postfix_expression = malloc(sizeof(char) * 100);
    int i = 0;
    int j = 0;
    while (infix_expression[i] != '\0') {
        if (isdigit(infix_expression[i])) {
            postfix_expression[j] = infix_expression[i];
            j++;
        }
        else if (infix_expression[i] == '(') {
            push(sPtr, infix_expression[i]);
        }
        else if (infix_expression[i] == ')') {
            while (peek(*sPtr) != '(') {
                postfix_expression[j] = pop(sPtr);
                j++;
            }
            pop(sPtr);
        }
        else if (isOperator(infix_expression[i])) {
            while (!isEmpty(*sPtr) && peek(*sPtr) != '(' && infix_expression[i] <= peek(*sPtr)) {
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
                    push(sPtr, operand1 + operand2);
                    break;
                case '-':
                    push(sPtr, operand1 - operand2);
                    break;
                case '*':
                    push(sPtr, operand1 * operand2);
                    break;
                case '/':
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
int isValidExpression(const char *userAnswer, int given[4]) {
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
            return 0;
        }
        i++;
    }
    if (numOpenParentheses != numCloseParentheses) {
        return 0;
    }
    if (numOperators != numOperands - 1) {
        return 0;
    }
    if(!isNumsUsedOnce(userAnswer, given)){
        return 0;
    }
    return 1;
}

//Checks if a character is a valid symbol
int isValidSymbol(char c) {
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == ' ';
}

//Checks if the numbers are used only once
int isNumsUsedOnce(const char *userAnswer, const int given[4]){

    int num_count[10] = {0}; // Initialize an array for counting the occurrences of each digit (0-9)
    int given_num_count[10] = {0}; // Initialize an array for counting the occurrences of each given number

    // Count the occurrences of each given number
    for (int i = 0; i < 4; i++) {
        given_num_count[given[i]]++;
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
    printf("Your choice --> \n");
}

//get puzzle from file
int* getPuzzle(const char *fileName) {

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

    char *puzzle[numberOfPossiblePuzzles];
    rewind(file);
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        puzzle[i] = malloc(strlen(line) + 1);
        strcpy(puzzle[i], line);
        i++;
    }

    int randomPuzzle = rand() % numberOfPossiblePuzzles;
    char *randomPuzzleString = puzzle[randomPuzzle]; //TODO Change return type to char* and do conversion to int in isNumsUsedOnce localy, not here.

    //store the numbers in the puzzle in an int array
    int given[4];
    int j = 0;
    for (int i = 0; randomPuzzleString[i] != '\0'; i++) {
        if (isdigit(randomPuzzleString[i])) {
            given[j] = randomPuzzleString[i] - '0';
            j++;
        }
    }

    //Print the puzzle in this format: "The numbers to use are: 4, 4, 8, 8."
    printf("The numbers to use are: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", given[i]);
        if (i != 3) {
            printf(", ");
        }
    }
    printf(".\n");
   

    //close file
    fclose(file);

    //return the puzzle
    return *given;

}

//play the round with given puzzle
//Return 1 if the user wins, 0 if the user loses
int playRound(int* given) {

    printf("Enter your solution: ");
    char *userAnswer = malloc(256);
    fgets(userAnswer, 256, stdin);
    userAnswer[strlen(userAnswer) - 1] = '\0';//remove the newline character

    //check if the user entered a valid expression
    if (!isValidExpression(userAnswer, given)) {
        printf("Invalid expression.\n");
        return 0;
    }

    //evaluate the user's expression
    int result = evaluateExpression(userAnswer);

    //Check if the user's answer is correct
    if (result == 24) {
        printf("Well done! You are a math genius.\n");
        return 1;
    } else {
        printf("Sorry. Your solution did not evaluate to 24.\n");
        return 0;
    }

}

//After round is played prompt user to play again or quit
/*Enter: 1 to play again,
2 to change the difficulty level and then play again, or
3 to exit the program.
Your choice --> */
int afterRoundMenu(){
    printf("Enter: 1 to play again,\n");
    printf("2 to change the difficulty level and then play again, or\n");
    printf("3 to exit the program.\n");
    printf("Your choice --> ");
    int choice;
    scanf("%d", &choice);
    return choice;
}


//TODO - given is empty when passed to playRound.