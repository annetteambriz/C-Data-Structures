#include <stdio.h> // for use of printf
#include <stdlib.h>
#include "LinkedList.h" // include linked list functions
#include "UserData.h" // UserData struct is need when we call the list functions

/****************************************************
SinglyLinkedListTester
This is a simple demonstration of the singly linked list functions.

It demos the abilities to:
      Make a linked list - uses call to LL_Init()
      Add items to the front of the list - uses call to LL_AddToFront()
      Add items to the end of the list - uses call to LL_AddToEnd()
      Get whatever item is at the front of the list, optionally deleting it
          - uses call to LL_GetFront with option to delete or retain the data
      Treat the list like an array, getting an item by specifying the
          index of the item (0 is the front) - uses call to LL_GetAtIndex()
      See how many items are inside the list - we call LL_Length()
      to return the item count.
*****************************************************/

/**
 PrintLL is a local function that we can call to print out a message (msg) and then
 the list contents (theLL).  So we can see how many things are allocated as we proceed,
 it will also print out the number of things allocated
**/
static void PrintLL (char msg[], LLInfoPtr theLL);

/** PrintLLItem is a local function that we can call to print out a message (msg) and
a UserData item.  So we can see how many things are allocated as we proceed,
it will also print out the number of things allocated
**/
static void PrintLLItem (char msg[], UserData D);

/**
AllocationCount is declared for global use in the list code itself.  We extern it so that
we can see how the allocations are increasing or decreasing.
**/
extern int AllocationCount;

/**
GetData is a function that populates an array with UserData
structs.
**/
UserData* getData(char filepath[], int size);

// Define constants
#define ARRAY_SIZE 7
#define INPUT_DATA "../testData.txt"

int main(int argc, const char * argv[]) {
    // The demo data in an array of UserData, where each item is an int
    //UserData DemoData[ARRAY_SIZE];

    // get data from a file
    UserData * DemoData = getData(INPUT_DATA, ARRAY_SIZE);
    int NumDemoDataItems = ARRAY_SIZE;

    // Initialize a LinkedList
    LLInfoPtr LL = LL_Init();

    PrintLL ("Starting demo...\nThe LL has been initialized.", LL);
    // add the array content to the list at the front
    for (int loop=0; loop < NumDemoDataItems; loop++)
    {
        UserData D;
        D = DemoData[loop];
        LL_AddAtFront (LL, D);
    }
    PrintLL ("Data has been placed at the front of the LL.", LL);
    // delete the list
    LL = LL_Delete(LL);
    PrintLL ("The LL has been deleted.", LL);

    // create another LL to demonstrate loading the array content from the end
    LL = LL_Init();
    PrintLL ("The LL has been initialized.", LL);
    // add the array content to the list at the end
    for (int loop = 0; loop < NumDemoDataItems; loop++)
    {
        UserData D;
        D = DemoData[loop];
        LL_AddAtEnd(LL, D);
    }
    // print out the data in the LL
    PrintLL ("Data items have been added at the end of the LL.", LL);

    // swap the items in the LL and print out the result
    for (int loop = 0; loop < LL_Length(LL)/2; loop++)
        LL_Swap(LL, loop, LL_Length(LL)- loop - 1);
    // print out the number of items in the LL
    PrintLL ("After data has been swapped in the LL.", LL);

    // Check out the ability to get a few items from the front of the LL
    // deleting the items
    for (int loop = 0; loop < 2; loop++)
        if (LL_Length(LL) > 0)
        {
        UserData D = LL_GetFront(LL, DELETE_NODE);
        PrintLLItem ("A data item has been removed from the front of the LL.", D);
        }
    PrintLL ("Data has been removed from the LL.", LL);
    LL = LL_Delete(LL);
    PrintLL ("The LL has been deleted.", LL);
    return 0;
}

/**
 Function PrintLL is called to print out a message, followed by the contents of the list
To determine the items to print, it uses the LL_Length function to get the list size
and then calls the LL_GetAtIndex function to read the UserData for each node in the list.
**/
void PrintLL (char msg[], LLInfoPtr theLL)
{
    printf("----------------------------\n");
    printf("%s\n", msg);
    printf("----------------------------\n");
    printf("Current state...\n");
    printf("\nNumber of items in Linked List: %d\n", LL_Length(theLL));
    printf("Allocation count: %d\n", AllocationCount);
    for (int loop = 0; loop < LL_Length(theLL); loop++)
    {
        UserData D = LL_GetAtIndex(theLL, loop);
        if (loop == 0)
            printf  ("Head==> [%d] = %d %s \n", loop, D.importance, &*D.taskName);
        else if (loop == LL_Length(theLL)-1)
            printf  ("Tail==> [%d] = %d %s \n", loop, D.importance, &*D.taskName);
        else printf ("        [%d] = %d %s \n", loop, D.importance, &*D.taskName);
    }
}

/**
Function PrintLLItem is called to print out a message, followed by the contents of a
UserData.
After logging the data content, it logs the number of remaining allocations.
**/
void PrintLLItem (char msg[], UserData D)
{
    printf ("%s \nthe UserData contained %d %s\n", msg, D.importance, &*D.taskName);
    printf ("The allocation count is now %d\n", AllocationCount);

}

/****************************************************
Function: getData
Summary:
GetData is a function that populates an array with UserData
structs. It is passed the file name to open / read / close.

Parameters:
    filePath - file pointer to file containing data.
    size - the maximum number of array entries to populate.

Returns:
    UserData* - a pointer to the array containing the UserData

*****************************************************/
UserData* getData(char filepath[], int size) {
    // Allocate memory for UserData array
    UserData *userData = malloc(size * sizeof(UserData));

    // attempt to open the file
    FILE* testData = fopen(filepath, "r");

    // exit if the file did not open
    if (testData == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    // initialize a counter to track the number of employee records
    int count = 0;

    // while count is less than the size
    // read records from the file, storing each record in the userData array
    do {
        int numInput = fscanf(testData, "%d %s",
                              &userData[count].importance,
                              userData[count].taskName);

        // ensure the number of fields is as expected
        if (numInput != 2)
            break;

        // increment count of number of employees processed
        count++;
    } while(count < size); // prevent overflow of employee records in the array

    // we have stopped reading, so close the file and exit
    fclose (testData);

    // return pointer to userData array
    return userData;
}

