#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
//
//  Queue.h - enhanced to support priority
//


// The calls on a Queue need to pass or return UserData
#include "UserData.h"
// Our Queue will use a linked list, so we need to resolve LLInfoPtr
#include "LinkedList.h"
// The Queue empty() call returns a boolean
#include <stdbool.h>

// To support maintaining priority in the queue, we declare a
// typedef that says "UserComparison is any function that, when
// called will receive 2 UserData to compare and return a boolean
// based on the comparison (true if first is of higher priority
// and false if not
typedef bool (*UserComparison) (UserData first, UserData second);

// This is the layout of a priority queue.  Notice that it contains
// a pointer to our underlying linked list, a simple boolean
// to indicate if our queue is empty (true) or not empty (false) and
// a pointer to the user's function called to support prioritization
// Notice the use of the typedef UserComparison
typedef struct {
    LLInfoPtr LL;
    bool empty;
    UserComparison Priority;
} QueueInfo, *Queue;


// initQueue() allocates a priority queue and initializes the
// priority queue structure
   Queue initQueue (UserComparison UserOrder);
// empty() returns the boolean for the Queue Q (true is empty, false is not empty)
bool        empty(Queue Q);
// enqueue() places the UserData at the end of the underlying LL
void        enqueue (Queue Q, UserData D);
// dequeue() returns the UserData on the top of the queue and deletes
// the data from the queue
UserData    dequeue (Queue Q);
// peek() returns the UserData on the top of the queue but will not
// delete it from the queue
UserData    peek (Queue Q);
// deleteQueue() deletes the frees the storage that was allocated by the call
// to initQueue()
Queue deleteQueue(Queue Q);

#endif // QUEUE_H_INCLUDED
