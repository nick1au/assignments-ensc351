/*
ENSC 351 - SAT Assignment
Win Aung - 301291027 - RAUNG@sfu.ca
Nicholas Lau - 301290893 - NLA52@sfu.ca
Submitted 2018-12-05
*/

//////////////////////////////////////
// Include libraries
//////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "string.h"
#include <omp.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

//////////////////////////////////////
// Global Variables
//////////////////////////////////////

int counting_backward = 0;
int total_variables = 0;
int total_clauses = 0;

//////////////////////////////////////
// Global Constants
//////////////////////////////////////

const int minimum_int = INT_MIN;

struct Stack{
    unsigned int size;
    int top;
    int* array_clause;
};

//////////////////////////////////////
// Helper Functions
//////////////////////////////////////

// Create a new stack with a placeholder clause representing the top
struct Stack* newStack(unsigned int size)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->size = size;
    stack->array_clause = (int*) malloc(stack->size*sizeof(int));
    for(unsigned int i = 0; i < size; i++)
    {
        stack->array_clause[i] = 0;
    }
    return stack;
}

// Check if the stack is full or not
bool Full_or_not(struct Stack* stack)
{
    return stack->top == stack->size - 1;
}

// Check if stack is empty
bool Empty_or_not(struct Stack* stack)
{
    return stack->top == -1;
}

// Pop the top-most element
int popstack(struct Stack* stack)
{
    if(Empty_or_not(stack))
        return minimum_int;
    int num = stack->array_clause[stack->top];
    stack->array_clause[stack->top] = 0;
    stack->top = stack->top - 1;
    return num;
}

//Add an element to the stack
void pushstack(int num, struct Stack* stack)
{
    if(!Full_or_not(stack))
        stack->array_clause[++stack->top] = num;
}

// Push a number to the clause
char* addnumbertoarray(char* array_clause, char character)
{
    size_t length = strlen(array_clause);
    char* num = malloc(length+2);
    strcpy(num, array_clause);
    num[length] = character;
    num[length+1] = '\0';
    return num;
}

// Find a solution (SAT) using the stack
bool findingsolution(struct Stack* solutionstack)
{
    for(int i = 0; i < solutionstack->top+2; i++)
    {
        if(Full_or_not(solutionstack))
            return false;
        if(abs(solutionstack->array_clause[i]) != i+1)
        {
            pushstack(i+1, solutionstack);
            return true;
        }
    }
    return false;
}

// Comparison function for clause and a given array int
bool same_or_not(int* given_clause, int* num, int current)
{
    for(unsigned int i = 0; i < current+1; i++)
    {
        if(given_clause[0] == 0)
            return false;
        for(unsigned int j = 0; j < current+1; j++)
        {
            if(num[i] == 0)
                break;
            if(num[i] == given_clause[j])
                return true;
        }
    }
    return false;
}

// Backtrack Function
bool goingback(struct Stack* solutionstack)
{
    static bool goback = false;

    if(solutionstack->top < 0)
        return false;

    if(solutionstack->array_clause[solutionstack->top] < 0)
    {
        popstack(solutionstack);
        counting_backward = counting_backward + 1;
        // Print the current backtrack if every 2 seconds
        if(!goback && time(0) % 2 == 0)
        {
            printf("Current Backtracking: %d \n", counting_backward);
            goback = true;
        }
        if(goback && time(0) % 2 == 1)
            goback = false;
        return goingback(solutionstack);
    }

    if(solutionstack->array_clause[solutionstack->top] > 0)
    {
        int num = popstack(solutionstack);
        num = num * -1;
        pushstack(num,solutionstack);
        return true;
    }

    

    
    return true;
    
}

//////////////////////////////////////
// Main Program
//////////////////////////////////////

int main(int argc, char const *argv[])
{

    // Open the file
    FILE* filename = fopen("file.txt", "r");
    if(filename == NULL)
    {
        fprintf(stderr, "Error opening the file");
        exit(EXIT_FAILURE);
    }

    char character = 'x';
    char* num = "";
    int currentvariable = 0;
    int currentclause = 0;
    int clause = 0;
    int variable = 0;

    // Read the text file

    while(!isdigit(character))
    {
        character = fgetc(filename);
    }
    
    for(unsigned int i = 0; i < 2; i++)
    {
        while(!isspace(character))
        {
            num = addnumbertoarray(num, character);
            character = fgetc(filename);
        }
        if(i == 0)
        {
            currentvariable = atoi(num);
            num = "";
            character = fgetc(filename);
        }
        else{
            currentclause = atoi(num);
            num = "";
        }
    }

    int list_of_clause[currentclause][currentvariable+1];

    // Build the clauses

    for(int i = 0; i < currentclause; i++)
    {
        for(int j = 0; j < currentvariable + 1; j++)
        {
            // Fill with placeholder elements
            list_of_clause[i][j] = 0;
        }
    }

    while((character = fgetc(filename)) != EOF)
    {
        if(character == '\n')
            character = fgetc(filename);
        while(!isspace(character))
        {
            num = addnumbertoarray(num, character);
            // \377 is EOF (-1) converted to char
            if(character == '\377')
                break;
            character = fgetc(filename);
        }
        if(strcmp(num, "") == 0)
            continue;
        list_of_clause[clause][variable] = atoi(num);
        num = "";
        if(list_of_clause[clause][variable] == 0)
        {
            clause = clause + 1;
            variable = 0;
        }
        else
            variable = variable + 1;
    }

    // SAT Solver Section using Stack
    
    struct Stack* solutionstack = newStack(currentvariable);
    int* answer;
    bool answer_is_satisfied = false;
    bool clause_is_satisfied = false;

    // Run SAT Solver in a loop until
    // A) Solution Found
    // B) All potential solutions exhausted - no solution

    while(true)
    {
        while(findingsolution(solutionstack))
        { // Run the SAT Solver 
        }
        int number_of_satisfied = 0;
        answer = solutionstack->array_clause;

        // CHeck if the solution is correct
        #pragma omp parallel for
            for(unsigned int i = 0; i < currentclause; i++)
            {
                clause_is_satisfied = same_or_not(list_of_clause[i], answer, currentvariable);
                if(clause_is_satisfied)
                {
                    // Critical section modifying the number of satisfiable clauses
                    #pragma omp critical
                    number_of_satisfied = number_of_satisfied + 1;
                }
            }

        if(number_of_satisfied == currentclause)
        {
            answer_is_satisfied = true;
            break;
        }

        if(number_of_satisfied != currentclause && solutionstack->top+1 == currentvariable)
        {
            if(!goingback(solutionstack))
            {
                answer_is_satisfied = false;
                break;
            }
        }
    }
    // End loop here

    // Print the result on-screen

    if(answer_is_satisfied)
    {
        printf("Solutions are \n \t[");
        for(unsigned int i = 0; i < currentvariable; i++)
        {
            printf("%d ", answer[i]);
        }
        printf("]\n");
    }
    else {
        printf("No Solution. \n");
    }

    // Deallocate the stack

    free(solutionstack->array_clause);
    free(solutionstack);

    return 0;
}


