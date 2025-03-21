//
//  Stack.c
//

#include <stdlib.h> // stdlib provides malloc and free
#include <stdbool.h> // stdbool defines bool
#include <assert.h> // asserts are used for checking that the stack exists
#include "Stack.h" // calls the stack supports are included for consistency checking
// the stack uses a linked list to implement a stack behavior (LIFO)
// push and pop will be done from the list front.
#include "LinkedList.h"

/*
 initStack() allocates a stack structure and initializes its contents.
 This consists of creating the underlying linked list and declaring the
 stack to be empty
*/
Stack initStack()
{
    // allocate a stack structure and abort if the allocation failed
    Stack S = (Stack) malloc(sizeof(StackInfo));
    assert (S!= NULL);
    AllocationCount++;
    // allocate and initialize the underlying linked list
    S->LL = LL_Init();
    // we are empty until an item is pushed
    S->empty = true;
    // return the stack to the caller
    return S;
}

/*
 deleteStack() calls the linked list delete to free up all of its nodes and, on return,
 frees up the stack itself. It returns NULL to indicate that there is no longer a
 stack.
 */
Stack deleteStack(Stack S)
{
    assert (S != NULL);
    LL_Delete(S->LL);
    free (S);
    AllocationCount--;
    return NULL;
}

/*
  empty() returns the boolean indicating the stack is currently empty
 */
bool empty (Stack S)
{
    assert (S != NULL);
    return S->empty;
}

/* push() calls the linked list to place the UserData on to the front of
   the linked list. Since a push is being done, the stack is no longer empty
    so we update the empty bool to false.
*/
void push (Stack S, UserData D)
{
    assert (S != NULL);
    LL_AddAtFront(S->LL, D);
    S->empty = false;
}

/* 
   pop() will fetch the UserData at the front of the linked list and return it to
   caller.  It updates the stack empty status by seeing if the linked list was 
   holding only a single item before the removal from the linked list occurs.
*/
UserData pop (Stack S)
{
    assert (S!= NULL);
    S->empty = LL_Length(S->LL) == 1 ? true : false;
    return LL_GetFront(S->LL, DELETE_NODE);
}
/*
   peek() will return the UserData at the front of the stack, but leave the data
   no the stack by calling the linked list GetFront() with a RETAIN option
*/
UserData    peek (Stack S)
{
    assert ( (S != NULL) && (S->empty != true) );
    return LL_GetFront(S->LL, RETAIN_NODE);
}
