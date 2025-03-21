#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

// The LL functions use UserData
#include "UserData.h"

// The Linked List needs the definition of what a Node is. A Node has
// UserData and linkage information for both "next and "prev"
// for a doubly linked list).

typedef struct node
{
    UserData Data;
    struct node *next;
    struct node *prev;
} Node, *NodePtr;


// A LL Information block contains Head and Tail pointers to a LL
// For speed, it also contains a running count of the number of nodes
// currently in the LL started at Head and finishing at Tail.
// Head is used when adding or removing from the LL front,
// Tail is needed only when adding to the end of the LL
typedef struct {
    NodePtr Head;
    NodePtr Tail;
    int     NumNodesInList;
    } LLInfo, *LLInfoPtr;

// Verifying allocation / deallocation of dynamic memory is done through
// AllocationCount.  The variable is declared in LinkedList.c and is linked to
// through the extern
extern int AllocationCount;

// ShouldDelete is an enum that has two valid values called DELETE_NODE
// and RETAIN_NODE that are used in calling to get user data from the front
// of the LL
typedef int ShouldDelete;
enum ShouldDelete {DELETE_NODE=1, RETAIN_NODE=2};

// declarations for LL callable functions follow

// LL_Init allocates a LL Information structure, initializing Head, Tail and NumNodesInList
// and returning the address of the structure
LLInfoPtr       LL_Init         ();
// LL_Delete frees up the LL Information structure
LLInfoPtr       LL_Delete       (LLInfoPtr LLI_Ptr);
// LL_AddAtFront adds user data to the front of the underlying LL accessed through
// the LL Information struct
void            LL_AddAtFront   (LLInfoPtr LLI_Ptr, UserData     theData);
// LL_AddAtEnd adds user data to the Tail of the underlying LL accessed through the
// LL information struct
void            LL_AddAtEnd     (LLInfoPtr LLI_Ptr, UserData     theData);
// LL_GetFront returns the user data currently at the Head of the underlying LL and
//, optionally removes the user data from the LL
UserData        LL_GetFront     (LLInfoPtr LLI_Ptr, ShouldDelete Choice);
// LL_Length returns the number of nodes in the underlying LL
int             LL_Length       (LLInfoPtr LLI_Ptr);
// LL_GetAtIndex returns the node at the specified index starting at 0
UserData        LL_GetAtIndex   (LLInfoPtr, int FetchIndex);
// LL_SetAtIndex updates the node at the specified index starting at 0
void            LL_SetAtIndex   (LLInfoPtr LLI_Ptr, UserData D, int UpdateIndex);
// LL_Swap swaps the nodes in the underlying LL specified by indices starting at 0
void            LL_Swap         (LLInfoPtr LLI_Ptr, int Index1, int Index2);
#endif // LINKEDLIST_H_INCLUDED
