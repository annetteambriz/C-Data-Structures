
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

#include "Stack.h" // stack callable routines
#include "UserData.h" // UserData definition for making and getting stack data

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

//define constants
#define INPUT_DATA "../StackData.txt"

int main(int argc, const char * argv[]) {

    // Show the allocation count when we start
    PrintAllocations ("Startup");
    
    // create a stack and see the effect of on the number of allocations
    Stack S = initStack();
    PrintAllocations ("InitStack");

    // populate the stack with test data
    populateStack(INPUT_DATA, S);

    // pop and print the stack content
    // peek at the data before popping it so we can see what peek yields
    while (!empty(S))
    {
        PrintStackItem ("peek", peek(S));
        PrintStackItem ("pop", pop(S));
    }
    // delete the stack and see the effect on the allocations
    PrintAllocations ("Before deleteStack");
    deleteStack(S);
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
