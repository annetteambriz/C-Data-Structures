
// StackTester will demonstrate the init, push, peek, pop and delete
// for a stack.
//      - It builds a stack that holds UserData from the DemoData array
//      - it peeks at the stack, returning UserData
//      - It pops UserData from the stack, returning UserData
//      - it uses empty() to determine if the stack holds any data that
//          can be popped or peeked
//      - when done, it deletes the stack
// For demonstration purposes, it shows the number of allocations for
// everything it does.

#include <stdio.h> // printf support
#include <stdlib.h>
#include <string.h>

#include "Stack.h" // stack callable routines
#include "UserData.h" // UserData definition for making and getting stack data

//define constants
#define INPUT_DATA "../StackData.txt"

// SortChoice is an enum with two valid values
// Used for sorting on task number or task name.
typedef int SortChoice;
enum SortChoice {TASK_NUMBER=1, TASK_NAME=2};

// local functions

// PrintStackItem is a local function that we can call to print out a message (msg) and
// a UserData item.  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
static void PrintStackItem (char msg[], UserData D);

// PrintAllocations is a local function that will print out a message (msg) and the
// current global AllocationCount
static void PrintAllocations (char msg[]);

/**
populateStack is a function that populates a stack with UserData
from data in a file.
**/
void populateStack(char filepath[], Stack stack);

/**
sortStack is a function that sorts a stack given a sortChoice
enum.
**/
Stack sortStack(Stack inputStack, SortChoice SortChoice);

int main(int argc, const char * argv[]) {

    // Show the allocation count when we start
    PrintAllocations ("Startup");
    
    // create a stack and see the effect of on the number of allocations
    Stack S = initStack();
    PrintAllocations ("InitStack");

    // populate the stack with test data
    populateStack(INPUT_DATA, S);

    Stack sorted = sortStack(S, TASK_NUMBER);

    // pop and print the stack content
    // peek at the data before popping it so we can see what peek yields
    while (!empty(sorted))
    {
        PrintStackItem ("peek", peek(S));
        PrintStackItem ("pop", pop(S));
    }
    // delete the stack and see the effect on the allocations
    PrintAllocations ("Before deleteStack");
    deleteStack(S);
    deleteStack(sorted);
    PrintAllocations ("DeleteStack");
    return 0;
}

/*
   PrintStackData prints out the received message and the data in UserData
*/
void PrintStackItem (char msg[], UserData D)
{
    printf ("\tAction: %s \tData: %d %s \tCurrent number of allocations: %d\n", msg, D.taskNumber, D.taskName, AllocationCount);
}

/* 
   PrintAllocations prints out the received message and the current allocation count
   The allocation count is global AllocationCount
*/
void PrintAllocations (char msg[])
{
    printf("\n========================================\n");
    printf("   %s\n", msg);
    printf ("   Current number of allocations: ""%d\n", AllocationCount);
    printf("========================================\n\n");
}

/****************************************************
Function: populateStack
Summary:
populateStack is a function that populates a stack with UserData
structs. Data is passed in from a file name to open / read / close.

Parameters:
    filePath - file path to file containing data.
    stack - the stack to add data to and populate.

Returns:
    Void

*****************************************************/
void populateStack(char filepath[], Stack stack) {
    // attempt to open the file
    FILE* testData = fopen(filepath, "r");

    // exit if the file did not open
    if (testData == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    // while not at the end of the file,
    // read records from the file, use each record to create UserData
    // and push it to the stack
    do {
        UserData D;
        int numInput = fscanf(testData, "%d %s",
                                &D.taskNumber,
                                D.taskName);

        push (stack, D);
        PrintStackItem("push", D);

        // ensure the number of fields is as expected
        if (numInput != 2)
            break;

    } while(!feof(testData)); // Loop until the end of the file

    // we have stopped reading, so close the file and exit
    fclose (testData);
}

/****************************************************
Function: sortStack
Summary:
sortStack is a function that sorts a stack with given a
SortChoice. Can be sorted by TASK_NUMBER or TASK_NAME.
Creates a temporary stack to sort the given stack
then copies the temporary stack to the stack passed in.

Parameters:
    inputStack - the stack to sort.
    sortChoice - a SortChoice enum

Returns:
    Void

*****************************************************/
Stack sortStack2(Stack inputStack, SortChoice SortChoice) {
    Stack tempStack = initStack();
    PrintAllocations ("Temp Stack InitStack");

    while (!empty(inputStack)) {
        UserData currentInputStackUserData = pop(inputStack);

        // check singular conditions under which we would pop from the temp stack
        // and place the item onto the input stack
        while (!empty(tempStack) &&
            ((SortChoice == TASK_NUMBER && peek(tempStack).taskNumber > currentInputStackUserData.taskNumber) ||
                (SortChoice == TASK_NAME && strcmp(peek(tempStack).taskName, currentInputStackUserData.taskName) > 0))) {
            push(inputStack, pop(tempStack));
        }
        // This is reached when the tempStack is empty, but the inputStack is not.
        // indicating there are still more items to sort, so we push to the temp stack.
        push(tempStack, currentInputStackUserData);
    }
    return tempStack;
}

Stack sortStack(Stack inputStack, SortChoice SortChoice) {
    Stack tempStack = initStack();
    PrintAllocations ("Temp Stack InitStack");

    while (!empty(inputStack)) {
        UserData currentInputStackUserData = pop(inputStack);

        while (!empty(tempStack)) {
            // assign temp peeked variable to use for sort
            UserData currentTempStackUserData = peek(tempStack);

            // check which choice to sort on
            switch (SortChoice) {
                case TASK_NUMBER:
                    // if the task number of the temp stack is greater than the current
                    // task number from the input stack, pop the UserData from the temp stack
                    // and push it onto the input stack.
                    if (currentTempStackUserData.taskNumber > currentInputStackUserData.taskNumber)
                        push(inputStack, pop (tempStack));
                    else
                        break;

                case TASK_NAME:
                    if (strcmp(currentTempStackUserData.taskName, currentInputStackUserData.taskName) > 0)
                        push(inputStack, pop(tempStack));
                    else
                        break;

                default:
                    printf("Error, invalid sorting choice.\n");
                    exit(0);;
            }
        }
        // This is reached when the tempStack is empty, but the inputStack is not.
        // indicating there are still more items to sort.
        push(tempStack, currentInputStackUserData);
    }
    return tempStack;
}