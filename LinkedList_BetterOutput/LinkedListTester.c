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
//static void PrintLL (char msg[], LLInfoPtr theLL);

// PrintLLitem is a local function that we can call to print out a message (msg) and
// a UserData item.  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
//static void PrintLLItem (char msg[], UserData D);

// AllocationCount is declared for global use in the list code itself. We extern it so that
// we can see how the allocations are increasing or decreasing.
extern int AllocationCount;

// The array size used
#define ARRAYSIZE 7

void PrintLL (char *msg, LLInfoPtr theLL);
void PrintLLItem (char *msg, UserData D);

int main() {
    // The demo data in an array of UserData, where each item is an int
    UserData DemoData[ARRAYSIZE];

    // Fill the array for the tests
    for (int loop = 0; loop < 7; loop++)
        DemoData[loop].num = 10 * (loop + 1);
    int NumDemoDataItems = 7;

    // ========================================
    // Initializing the Linked List
    // ========================================
    LLInfoPtr LL = LL_Init();
    PrintLL("Starting demo.", LL);

    // ========================================
    // Adding Data at the Front
    // ========================================
    for (int loop = 0; loop < NumDemoDataItems; loop++) {
        UserData D = DemoData[loop];
        LL_AddAtFront(LL, D);
    }
    PrintLL("After data has been placed at the front of the LL...", LL);

    // Deleting the list
    LL = LL_Delete(LL);
    PrintLL("After the LL has been deleted...", LL);

    // ========================================
    // Reinitializing the Linked List
    // ========================================
    LL = LL_Init();
    PrintLL("After the LL has been initialized...", LL);

    // ========================================
    // Adding Data at the End
    // ========================================
    for (int loop = 0; loop < NumDemoDataItems; loop++) {
        UserData D = DemoData[loop];
        LL_AddAtEnd(LL, D);
    }
    PrintLL("After data items have been added at the end of the LL...", LL);

    // ========================================
    // Swapping Data
    // ========================================
    for (int loop = 0; loop < LL_Length(LL) / 2; loop++)
        LL_Swap(LL, loop, LL_Length(LL) - loop - 1);
    PrintLL("After data has been swapped in the LL...", LL);

    // ========================================
    // Removing Data from the Front
    // ========================================
    for (int loop = 0; loop < 2; loop++) {
        if (LL_Length(LL) > 0) {
            UserData D = LL_GetFront(LL, DELETE_NODE);
            PrintLLItem("A data item has been removed from the front of the LL..", D);
        }
    }
    PrintLL("After data has been removed from the LL..", LL);

    // ========================================
    // Final Deletion
    // ========================================
    LL = LL_Delete(LL);
    PrintLL("After the LL has been deleted...", LL);

    return 0;
}

// ========================================
// Print Linked List Status
// ========================================
void PrintLL (char *msg, LLInfoPtr theLL) {
    printf("\n========================================\n");
    printf("   %s\n", msg);
    printf("========================================\n");

    printf("- Current status:\n");
    printf("    Items: %d\n", LL_Length(theLL));
    printf("    Allocation count: %d\n", AllocationCount);

    if (LL_Length(theLL) == 0) {
        printf("    (The list is empty)\n");
    } else {
        printf("\n  List Content (Head → Tail):\n");
        for (int loop = 0; loop < LL_Length(theLL); loop++) {
            UserData D = LL_GetAtIndex(theLL, loop);
            if (loop == 0)
                printf("    [%d] = %d (Head)\n", loop, D.num);
            else if (loop == LL_Length(theLL) - 1)
                printf("    [%d] = %d (Tail)\n", loop, D.num);
            else
                printf("    [%d] = %d\n", loop, D.num);
        }
    }
    printf("\n");
}

// ========================================
// Print Removed Item
// ========================================
void PrintLLItem (char *msg, UserData D) {
    printf("\n----------------------------------------\n");
    printf("%s\n", msg);
    printf("----------------------------------------\n");
    printf("- The UserData contained: %d\n", D.num);
    printf("- Allocation count is now: %d\n", AllocationCount);
}
