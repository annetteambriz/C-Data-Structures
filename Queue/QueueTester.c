
// QueueTester will demonstrate the init, enqueue, peek, dequeue and delete
// for a queue.
//      - It builds a queue that holds UserData from the DemoData array
//      - it peeks at the queue, returning UserData
//      - It dequeues UserData from the queue, returning UserData
//      - it uses empty() to determine if the queue holds any data that
//          can be dequeued or peeked
//      - when done, it deletes the queue
// For demonstration purposes, it shows the number of allocations for
// everything it does.

// printf support
#include <stdio.h>
// queue callable routines
#include "Queue.h"
// UserData definition for making and getting queue data
#include "UserData.h"
// local functions

// PrintQueueItem is a local function that we can call to print out a message (msg) and
// a UserData item.  So we can see how many things are allocated as we proceed,
// it will also print out the number of things allocated
static void PrintQueueItem (char msg[], UserData D);

// PrintAllocations is a local function that will print out a message (msg) and the
// current global AllocationCount
static void PrintAllocations (char msg[]);

int main(int argc, const char * argv[]) {
    //The demo data we use is an array of UserData, where each item is an int
   UserData DemoData[] = { {1000}, {2000}, {3000}, {4000} };
   // A convenient way to determine how many items are in an array
   // is to take the size of the array and divide it by the size of
   // a single array item.  That gives you the number of items in
   // the array
   int NumDemoDataItems = sizeof(DemoData) / sizeof(DemoData[0]);
   // Show the allocation count when we start
   PrintAllocations ("On startup");

   // create a queue and see the effect of on the number of allocations
   Queue Q = initQueue();
   PrintAllocations ("After initQueue called");

   // enqueue the data on the queue, showing the data and allocations
   for (int loop = 0; loop < NumDemoDataItems; loop++)
   {
       UserData D = DemoData[loop];
       enqueue (Q, D);
       PrintQueueItem("enqueue called, data is", D);
   }
   // dequeue and print the queue content
   // peek at the data before dequeue-ing it so we can see what peek yields
   while (!empty(Q))
   {
       PrintQueueItem ("peek    called, data is", peek(Q));
       PrintQueueItem ("dequeue called, data is", dequeue(Q));
   }
   // delete the queue and see the effect on the allocations
   PrintAllocations ("Before deleteQueue called");
   Q = deleteQueue(Q);
   PrintAllocations ("After deleteQueue called");
    return 0;
}

/*
   PrintQueueItem prints out the received message and the data in UserData
*/
void PrintQueueItem (char msg[], UserData D)
{
    printf ("%s %d, #allocations is %d\n", msg, D.taskNumber, AllocationCount);
}

/*
   PrintAllocations prints out the received message and the current allocation count
   The allocation count is global AllocationCount
*/
void PrintAllocations (char msg[])
{
    printf ("%s, #allocations is %d\n", msg, AllocationCount);
}
