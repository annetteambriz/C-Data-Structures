
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

int main(int argc, const char * argv[]) {
    // The demo data we use is an array of UserData, where each item is an int
    UserData DemoData[] = { {1000}, {2000}, {3000}, {4000} };
    // A convenient way to determine how many items are in an array
    // is to take the size of the array and divide it by the size of
    // a single array item.  That gives you the number of items in
    // the array
    int NumDemoDataItems = sizeof(DemoData) / sizeof(DemoData[0]);
    // Show the allocation count when we start
    PrintAllocations ("On startup");
    
    // create a stack and see the effect of on the number of allocations
    Stack S = initStack();
    PrintAllocations ("After initStack called");

    // push the data on the stack, showing the data and allocations
    for (int loop = 0; loop < NumDemoDataItems; loop++)
    {
        UserData D = DemoData[loop];
        push (S, D);
        PrintStackItem("push called, data is", D);
    }
    // pop and print the stack content
    // peek at the data before popping it so we can see what peek yields
    while (!empty(S))
    {
        PrintStackItem ("peek called, data is", peek(S));
        PrintStackItem ("pop  called, data is", pop(S));
    }
    // delete the stack and see the effect on the allocations
    PrintAllocations ("Before deleteStack called");
    S = deleteStack(S);
    PrintAllocations ("After deleteStack called");
    return 0;
}

/*
   PrintStackData prints out the received message and the data in UserData
*/
void PrintStackItem (char msg[], UserData D)
{
    printf ("%s %d, #allocations is %d\n", msg, D.num, AllocationCount);
}

/* 
   PrintAllocations prints out the received message and the current allocation count
   The allocation count is global AllocationCount
*/
void PrintAllocations (char msg[])
{
    printf ("%s, #allocations is %d\n", msg, AllocationCount);
}
