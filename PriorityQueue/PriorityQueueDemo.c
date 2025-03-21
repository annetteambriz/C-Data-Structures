// PriorityQueueDemo.c demonstrates the use of the initQueue, buildQueue, enqueue, dequeue
// for a priority queue.
//      - It builds a queue that holds UserData generated via the genTimePriorityUserData()
//        which uses system time and a random number for priority.
//      - After data is enqueued, if a UserComparison function has been provided at the time of the
//      initQueue call, then the nodes within the queue are swapped or adjusted until they are in order
//      of priority as defined by the UserComparison function.
//      - It dequeues UserData from the queue, returning UserData
//      - it uses empty() to determine if the queue holds any data that
//          can be dequeued or peeked
//      - when done, it deletes the queue
// For demonstration purposes, it shows the number of allocations for
// everything it does.

#include <stdio.h>
// we will use rand() and srand() from stdlib.h
// we will be getting system data and time from time.h
#include <time.h>
#include <stdlib.h>
// we will use strcpy() and strlen() from string.h
#include <string.h>
// we use a bool from stdbool.h
#include <stdbool.h>
// we use Queue functions from Queue.h
#include "PriorityQueue.h"
// we use UserData for the queue
#include "UserData.h"

#define MAXPRIO 4
#define DEQUEUES_PER_ENQUEUE 3
#define INITIAL_ENQUEUES 15

// function declarations provided in this file

static void          Runtest (Queue Q);
static void          buildQueue (Queue Q, int numItems);
static UserData      genTimePriorityUserData ();
static bool          LowestNumIsHighestPriority (UserData first, UserData second);
static bool          HighestNumIsHighestPriority (UserData first, UserData second);

/*
 * Verifying allocation / deallocation of dynamic memory is done through
 * AllocationCount.  The variable is declared in LinkedList.c and is linked to
 * through the extern
*/
extern int AllocationCount;

/*
 * This function is used by Runtest() to generate UserData to fill a queue
 * using the genTimePriorityUserData() function. The generated UserData is
 * enqueued to the Queue passed into the function of the number of items specified
 * by the numItems int. Since the Queue pointer is passed in there is no need to return
 * anything. The given Queue has been modified and filled or built.
 *
 */
void buildQueue (Queue Q, int numItems)
{
    for (; numItems > 0; numItems--)
    {
        UserData D = genTimePriorityUserData();
        enqueue (Q, D);
        printf ("Time = %s queued at priority %d\n", D.time, D.priority);
    }
}

//****************************************************
// Function: genTimePriorityUserData
//    This function fills a UserData structure with the current
//    system time and a random priority from 1 to MAXPRIO.
//    Before exiting, this routine spins for 1 second so
//    that another, immediate call will have a different
//    time stamp.  It then returns the populated UserData.
//*****************************************************
UserData genTimePriorityUserData ()
{
    // get the current time
    time_t current_time = time(NULL);
    // convert it to ASCII and point to it
    char* theTime = ctime(&current_time);
    // trim off the \n for prettier printing
    for (int loop = 0; loop < strlen(theTime); loop++)
        if (theTime[loop] == '\n')
            theTime[loop] = 0;
    // fill in time and a priority (1 to MAXPRIO)
    UserData D;
    strcpy (D.time, theTime);
    D.priority = 1 + rand() % MAXPRIO;
    // spin for at least 1 second so that the time field will
    // be different if we are called again immediately
    time_t time_now;
    do
    {
        // get the current time (seconds)
        time_now= time(NULL);
        // spin here if it hasn't changed by at least 1 second
    }
    while ((time_now - current_time) == 0);
    return D;
}

// LowestNumIsHighestPriority is called by the queue
// whenever the queue needs to be updated to maintain priority
// such that the items with the lowest priority numbers will
// be treated as the highest priority items when dequeueing is done.
// It returns a bool "true" if first.priority <= second.priority
bool LowestNumIsHighestPriority (UserData first, UserData second)
{
    // treat the lower priority number as more important
    if (first.priority <= second.priority)
        return true;
    else
        return false;
}

// HighestNumIsHighestPriority is called by the queue
// whenever the queue needs to be updated to maintain priority
// such that the items with the higher priority numbers will
// be treated as the highest priority items when dequeueing is done.
// It returns a bool "true" if first.priority > second.priority
bool HighestNumIsHighestPriority (UserData first, UserData second)
{
    // treat the lower priority number as more important
    if (first.priority > second.priority)
        return true;
    else
        return false;
}

/*
 * A subroutine that is run by the main function to call buildQueue()
 * Print out contents of the queue, and dequeue items while the queue is not
 * empty.
 */
void Runtest (Queue Q)
{
    // seed the random number generator so it doesn't always
    // start with the same value
    time_t t;
    srand((unsigned) time(&t));
    // start with a queue filled with INITIAL_ENQUEUES items of random priority
    // buildQueue will ensure that the timestamps are separated by 1
    // second so we can see that priority queue behavior is done correctly
    buildQueue (Q, INITIAL_ENQUEUES);
    printf ("Total allocations is %d after buildQueue\n", AllocationCount);
    printf ("Starting to dequeue and queue information\n");
    // we will enqueue 1 item after dequeueing at most DEQUEUES_PER_ENQUEUE
    // items by priority unless the queue is exhausted.
    // if that happens, we are done
    int NumToDequeue = DEQUEUES_PER_ENQUEUE;

    // continue to dequeue items while the empty() function call with our QueueInfo
    // does not return True
    while (empty(Q) != true)
    {
        UserData D = dequeue (Q);
        printf ("  Allocation = %2d, dequeued data: ", AllocationCount);
        printf ("Priority %-3d Time = %s\n", D.priority, D.time);
        // if we have dequeued DEQUEUES_PER_ENQUEUE items, generate
        // and queue another one to show that the queue is intact
        // even if we have begun dequeue-ing items
        if (--NumToDequeue == 0)
        {
            // generate random data and a time stamp
            UserData D = genTimePriorityUserData();
            // add a UserData to the queue
            enqueue (Q, D);
            printf ("Time = %s queued at priority %d\n", D.time, D.priority);
            // reestablish how many items to dequeue before the next enqueue
            NumToDequeue = DEQUEUES_PER_ENQUEUE;
        }
    }
    // only the allocation of the queue itself remains to be freed
    printf ("Total allocations is %2d after all the dequeue calls\n", AllocationCount);
}

/*
 * A main function to test our queue functions with test data.
 * Initially runs a queue with no priority by passing NULL as the UserComparison function
 * to the initQueue() function. Runs Runtest() then deletes the Queue and its contents.
 *
 * The second run passes the LowestNumIsHighestPriority function as the UserComparison function
 * to the initQueue() function. This prioritizes lower numbers over higher numbers, such that
 * a 1 will be a higher priority over a 2. Runs Runtest() then deletes the Queue and its contents.
 *
 * Thirdly, the HighestNumIsHighestPriority function is passed in as the UserComparison function
 * which prioritizes a higher number over a lower number. Runs Runtest() then deletes the Queue and its contents.
 *
 * In each call Runtest() function call the queue is filled with UserData by calling
 * the buildQueue() function. This function calls genTimePriorityUserData() which creates
 * UserData structures with the current system time and a random priority from 1 to MAXPRIO,
 * then buildQueue() enqueues them to the queue, if a priority function in provided AdjustQueue() will
 * swap nodes until the enqueued node is where "it should be" based on its priority. The function
 * then prints out the contents that were enqueued.
 * Afterwards, Runtest() prints outs the AllocationCount and dequeues the contents of the queue.
 *
 */
int main()
{
    // first run no priority
    printf ("\nDemonstrating how the queue works WITHOUT a priority application\n");
    // provide NULL so that no priority check will be done
    Queue Q = initQueue(NULL);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    deleteQueue (Q);
    printf ("After deleteQueue, remaining allocations is %d \n", AllocationCount);

    // second run, with LowestNumIsHighestPriority
    printf ("\n\nDemonstrating how the queue works WITH a priority application\n");
    printf ("The lowest priority number should be the highest priority to dequeue\n");
    // provide a routine to test priorities so that priority will be maintained
    Q = initQueue(LowestNumIsHighestPriority);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    deleteQueue (Q);

    // third run, with HighestNumIsHighestPriority
    printf ("\n\nDemonstrating how the queue works WITH a priority application\n");
    printf ("The highest priority number should be the highest priority to dequeue\n");
    // provide a routine to test priorities so that priority will be maintained
    Q = initQueue(HighestNumIsHighestPriority);
    printf ("Total allocations is %d after initQueue\n", AllocationCount);
    Runtest(Q);
    deleteQueue (Q);
    printf ("After deleteQueue, remaining allocations is %d \n", AllocationCount);

    return 0;
}
