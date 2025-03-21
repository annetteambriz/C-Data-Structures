//
//  SinglyLinkedListTester
//
//  This is a simple demonstration of the singly linked list functions.
//  It demos the abilities to:
//      Make a linked list - uses call to LL_Init()
//      Add items to the front of the list - uses call to LL_AddToFront()
//      Add items to the end of the list - uses call to LL_AddToEnd()
//      Get whatever item is at the fron of the list, optionally deleting it
//          - uses call to LL_GetFront with option to delete or retain the data
//      Treat the list like an array, getting or an item by specifying the
//          index of the item (0 is the front) - uses call to LL_GetAtIndex()
//      Whenever we want to see how many items are inside the list, we call
//          LL_Length() to return the item count.
//  This code has been "overly documented" so that it serves as a learning
//  piece of code.  Take the time to read and undersatand it!

// we use printf from stdio.h
#include <stdio.h>
// we use the linked list, so include its functions that we can call
#include "LinkedList.h"
// we use UserData when we call the list functions
#include "UserData.h"

// PrintLL is a local function that we can call to print out a message (msg) and then
// the list contents (theLL).  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
static void PrintLL (char msg[], LLInfoPtr theLL);

// PrintLLitem is a local function that we can call to print out a message (msg) and
// a UserData item.  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
static void PrintLLItem (char msg[], UserData D);

// AllocationCount is declared for global use in the list code itself.  We extern it so that
// we can see how the allocations are inceeasing or decreasing.
extern int AllocationCount;

// The array size used
#define ARRAYSIZE 7

int main(int argc, const char * argv[]) {
    // The demo data in an array of UserData, where each item is an int
    UserData DemoData[ARRAYSIZE];

    // fill the array for the tests
    for (int loop=0; loop < ARRAYSIZE; loop++)
        DemoData[loop].num = 10 * (loop+1);
    int NumDemoDataItems = ARRAYSIZE;

    // make a LinkedList to play with
    LLInfoPtr LL = LL_Init();
    PrintLL ("Starting demo.\nAfter the LL has been initialized...", LL);
    // add the array content to the list at the front
    for (int loop=0; loop < NumDemoDataItems; loop++)
    {
        UserData D;
        D = DemoData[loop];
        LL_AddAtFront (LL, D);
    }
    PrintLL ("After data has been placed at the front of the LL...", LL);
    // delete the list
    LL = LL_Delete(LL);
    PrintLL ("After the LL has been deleted...", LL);

    // create another LL to demonstrate loading the array content from the end
    LL = LL_Init();
    PrintLL ("After the LL has been initialized...", LL);
    // add the array content to the list at the end
    for (int loop = 0; loop < NumDemoDataItems; loop++)
    {
        UserData D;
        D = DemoData[loop];
        LL_AddAtEnd(LL, D);
    }
    // print out the data in the LL
    PrintLL ("After data items have been added at the end of the LL...", LL);

    // swap the items in the LL and print out the result
    for (int loop = 0; loop < LL_Length(LL)/2; loop++)
        LL_Swap(LL, loop, LL_Length(LL)- loop - 1);
    // print out the number of items in the LL
    PrintLL ("After data has been swapped in the LL...", LL);

    // Check out the ability to get a few items from the front of the LL
    // deleting the items
    for (int loop = 0; loop < 2; loop++)
        if (LL_Length(LL) > 0)
        {
        UserData D = LL_GetFront(LL, DELETE_NODE);
        PrintLLItem ("A data item has been removed from the front of the LL.. ", D);
        }
    PrintLL ("After data has been removed from the LL..", LL);
    LL = LL_Delete(LL);
    PrintLL ("After the LL has been deleted...", LL);
    return 0;
}

// function PrintLL is called to print out a message, followed by the contents of the list
// To determine the items to print, it uses the LL_Length function to get the list size
// and then calls the LL_GetAtIndex function to read the UserData for each node in the list.
void PrintLL (char msg[], LLInfoPtr theLL)
{
    printf ("%s\nThere are now %d items with an allocation count of %d\n",
            msg, LL_Length(theLL), AllocationCount);
    for (int loop = 0; loop < LL_Length(theLL); loop++)
    {
        UserData D = LL_GetAtIndex(theLL, loop);
        if (loop == 0)
            printf  ("Head==> [%d] = %d\n", loop, D.num);
        else if (loop == LL_Length(theLL)-1)
            printf  ("Tail==> [%d] = %d\n", loop, D.num);
        else printf ("        [%d] = %d\n", loop, D.num);
    }
}

// function PrintLLItem is called to print out a message, followed by the contents of a
// UserData.
// After logging the data content, it logs the number of remaining allocations.
void PrintLLItem (char msg[], UserData D)
{
    printf ("%s \nthe UserData contained %d\n", msg, D.num);
    printf ("The allocation count is now %d\n", AllocationCount);

}

