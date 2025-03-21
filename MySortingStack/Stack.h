//
//  Stack.h
//

#ifndef Stack_h
#define Stack_h

#include "UserData.h" // The calls on a stack need to pass or return UserData
#include "LinkedList.h" // Our stack will use a linked list, so we need to resolve LLInfoPtr
#include <stdbool.h> // The stack empty() call returns a boolean

/*
 *This is the layout of a stack.  Notice that it contains
 *a pointer to our underlying linked list and a simple boolean
 *to indicate if our stack is empty (true) or not empty (false)
*/

typedef struct {
    LLInfoPtr LL;
    bool empty;
} StackInfo, *Stack;

// initStack() allocates a stack and initializes it
Stack       initStack();

// empty() returns the boolean for the Stack S (true is empty, false is not empty)
bool        empty(Stack S);

// push() places the UserData on the top of the stack
void        push (Stack S, UserData D);

// pop() returns the UserData on the top of the stack and deletes
// the data from the stack
UserData    pop (Stack S);

// peep() returns the UserData on the top of the stack but will not
// delete it from the stack
UserData    peek (Stack S);

// deleteStack() deletes the frees the storage that was allocated by the call
// to initStack()
Stack       deleteStack(Stack S);

#endif /* Stack_h */
