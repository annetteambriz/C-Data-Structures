//
//  Queue.h
//

#ifndef Queue_h
#define Queue_h

// The calls on a Queue need to pass or return UserData
#include "UserData.h"
// Our Queue will use a linked list, so we need to resolve LLInfoPtr
#include "LinkedList.h"
// The Queue empty() call returns a boolean
#include <stdbool.h>

// This is the layout of a queue.  Notice that it contains
// a pointer to our underlying linked list and a simple boolean
// to indicate if our queue is empty (true) or not empty (false)

typedef struct {
    LLInfoPtr LL;
    bool empty;
} QueueInfo, *Queue;

// initQueue() allocates a queue and initializes it
Queue       initQueue();
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
Queue       deleteQueue(Queue Q);

#endif /* Queue_h */
