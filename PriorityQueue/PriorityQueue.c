//
//  Queue.c with priority support
//

// stdlib provides malloc and free
#include <stdlib.h>
// stdbool defines bool
#include <stdbool.h>
// asserts are used for checking that the queue exists
#include <assert.h>
// calls the queue supports are included for consistency checking
#include "PriorityQueue.h"
// the queue uses a linked list to implement a queue behavior (FIFO)
// enqueue and pop will be done from the list front.
#include "LinkedList.h"

// local function AdjustQueue is called whenever an enqueue is done
// to reorder the underlying list by priority, preserving the oldest
// enqueued order among equal priorities already in the queue
static void AdjustQueue (Queue Q);

/*
 initQueue() allocates a queue structure and initializes its contents.
 This consists of creating the underlying linked list, declaring the
 queue to be empty, and saving the pointer to the user function used
 to determine the priority in the queue

 IF NULL IS PASSED, THIS QUEUE WILL OPERATE AS A NORMAL QUEUE.
 IF THE USER'S PRIORITY COMPARISON FUNCTION ADDRESS IS PASSED, IT
 WILL BE CALLED TO DETERMINE WHERE IN THE QUEUE THE ENQUEUED DATA WILL
 RESIDE
*/
Queue initQueue(UserComparison UserOrder)
{
    // allocate a queue structure and abort if the allocation failed
    Queue Q = (Queue) malloc(sizeof(QueueInfo));
    assert (Q!= NULL);
    AllocationCount++;
    // allocate and initialize the underlying linked list
    Q->LL = LL_Init();
    // we are empty until an item is pushed
    Q->empty = true;
    // save the user's comparison function pointer
    Q->Priority = UserOrder;
    // return the queue to the caller
    return Q;
}

/*
 deleteQueue() calls the linked list delete to free up all of its nodes and, on return,
 frees up the queue itself.  it returns NULL to indicate that there is no longer a
 queue.
 */
Queue deleteQueue(Queue Q)
{
    assert (Q != NULL);
    LL_Delete(Q->LL);
    free (Q);
    AllocationCount--;
    return NULL;
}

/*
  empty() returns the boolean indicating the queue is currently empty
 */
bool empty (Queue Q)
{
    assert (Q != NULL);
    return Q->empty;
}

// AdjustQueue is a bubble sort that sorts by priority
// if the user provided a priority comparison
// support routine. If one is not provided, the
// function will leave the queue in the order
// that enqueue calls have been made.  That makes it
// operate as a simple queue.
void AdjustQueue (Queue Q)
{
    assert (Q != NULL);
    int Qsize = LL_Length(Q->LL);
    // we are done if there is no priority function
    // or there are 0 or 1 items in the queue
    if ((Q->Priority == NULL) || (Qsize < 2)) return;
    int i,j;
    // swapped false means that nothing has been
    // swapped, so the bubble sort can exit on sensing
    // it
    bool swapped;

    // loop through all UserData
    for(i = 0; i < Qsize-1; i++) {
        // swapped is the exit condition
        swapped = false;
        // loop through numbers falling ahead
        for(j = 0; j < Qsize-1-i; j++) {
            // check if UserData[j+1] is of higher priority than UserData[j]
            if (Q->Priority(LL_GetAtIndex(Q->LL, j+1), LL_GetAtIndex(Q->LL, j))) {
                // yes, so swap and flag that swapping is being done
                LL_Swap(Q->LL, j, j+1);
                swapped = true;
            }
        }
        // if nothing was swapped that means
        // queue is sorted now, so we are done.
        if(!swapped) {
            break;
        }
    }
}


/* enqueue() calls the linked list to place the UserData at the end of
   the linked list. Since an enqueue is being done, the queue is no longer empty.
   AdjustQueue is called to apply priority if the user provided
   a priority comparison function.
*/
void enqueue (Queue Q, UserData D)
{
    assert (Q != NULL);
    LL_AddAtEnd(Q->LL, D);
    Q->empty = false;
    AdjustQueue (Q);
}

/*
   dequeue() will fetch the UserData at the front of the linked list and return it to
   caller.  It updates the queue empty status by seeing if the linked list was
   holding only a single item before the removal from the linked list occurs.
*/
UserData dequeue (Queue Q)
{
    assert (Q!= NULL);
    Q->empty = LL_Length(Q->LL) == 1 ? true : false;
    return LL_GetFront(Q->LL, DELETE_NODE);
}
/*
   peek() will return the UserData at the front of the queue, but leave the data
   no the queue by calling the linked list GetFront() with a RETAIN option
*/
UserData    peek (Queue Q)
{
    assert ( (Q != NULL) && (Q->empty != true) );
    return LL_GetFront(Q->LL, RETAIN_NODE);
}
