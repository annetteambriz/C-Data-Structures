///////////////////////
/*
// This double linked list code is designed to be useful, without
// modification, for whatever the content of "UserData" is.
// The intent is to have a linked list that will support
//      - placing nodes at the front of a list,
//      - placing nodes at the end of a list
//      - reporting the number of nodes in a list,
//      - swapping node content or linkages,
//      - reading any node content,
//      - updating any node content, and
//      - returning and optionally deleting whatever node
//        is at the start of the list.
//
// It will directly support the stack, queue and priority
// queue data structures that we will use in the future
// weeks WITHOUT MODIFICATION OF ANY OF ITS CODE!
//
// WHY?... Here is how a stack and queue work...
//
//      Since a stack, queue and priority queue find
//      being able to "peek" at the next node they can access
//      without deleting the node, our returning a node will
//      always return the node at the front and have an option
//      to return it without deleting it.  That option will differentiate
//      between a peek and a pop / dequeue where the node is removed
//      from the list.

// The only complication will be when we create a priority
// queue and the subtlety of handling priority will be handled
// with the priority queue code itself.

// BOTTOM LINE...
The linked list will never understand what it is carrying as
data and how it is being used.  It will be easily used as the
basis for a stack, queue or priority queue for any UserData
content.
*/

// stdlib provides the definition of NULL and the declarations for
// malloc() and free()
#include <stdlib.h>
// assert is a macro that makes it VERY easy to check something and
// have your program exit and log the file and line number where
// the check failed.  It comes in very handy to add error checking
// without typing in a bunch of print statements
#include <assert.h>
// The linked list needs UserData to get the definition of what the
// structure containing the user's data in a node is.  The code needs
// the information only to be able to allocate a node and copy
// the user's data into a node.

// NOTE: C allows a struct to be copied without using any of the
// struct field names, and that is what we need to do so that the code
// does not get changed when "UserData" changes.
#include "UserData.h"

/* LinkedList.h contains two different things:
1. It defines a struct that contains the information needed
to use a linked list.  Typically, that is the "head" pointer
to the first node (the start of) the linked list.  We will
also use it to hold the running count of the number of
nodes in the linked list started by "head" and ending at "tail".
2. It declares the functions callable for a linked list.
*/
#include "LinkedList.h"

// To make sure we are allocating and deallocating dynamic memory,
// variable AllocationCount is declared within the LinkedList code
// and is referenced by any other code that does dynamic memory
// allocation and deallocation
int AllocationCount = 0;

// Locally called function declarations to follow

// MakeNode are called to allocate and initialize a node using the UserData
static NodePtr MakeNode (UserData theData);

// GetNodeAddress is used to return a pointer of an LL node, given an index
// It will return the address of the node w/o changing its value
static NodePtr GetNodeAddress (LLInfoPtr LLI_Ptr, int FetchIndex);

// Externally callable functions for a user of the Linked List follow

/*
// LL_Init is used to allocate and initialize a LinkedList
// Information structure.  It will update the AllocationCount
// to reflect the malloc of the struct and return the pointer
// to the struct for the caller to use when calling any
// other function in the linked list
*/
LLInfoPtr LL_Init()
{
    // Allocate a Linked List information structure
    LLInfoPtr LLI_Ptr = (LLInfoPtr) malloc (sizeof (LLInfo));
    assert (LLI_Ptr != NULL);
    // Initialize the data in the struct just allocated
    LLI_Ptr->Head = NULL;
    LLI_Ptr->Tail = NULL;
    LLI_Ptr->NumNodesInList = 0;
    // update AllocationCount to reflect the malloc
    AllocationCount++;
    // return the pointer to the allocated struct to the caller
    return LLI_Ptr;
}

/////////////
// LL_Delete is called to delete all the nodes in the Linked
// List identified by LL_Ptr.
// It does so by simply calling LL_GetFront to read
// each node with a delete option.  Once all the nodes
// have been deleted, it frees the memory associated with
// the LinkedList information struct and updates the AllocationCount
// to reflect the memory release.
/////////////
LLInfoPtr LL_Delete(LLInfoPtr LLI_Ptr)
{
    // We should not have been called if the Linked List
    // Information structure does not exist, so make sure
    // it does and exit if not.
    assert (LLI_Ptr != NULL);
    // To get rid of each node, simply read and delete each
    // node using LL_GETFRONT
    while (LLI_Ptr->NumNodesInList != 0)
        LL_GetFront(LLI_Ptr, DELETE_NODE);
    // Now that all the nodes are gone, delete the Information
    // structure itself
    free(LLI_Ptr);
    LLI_Ptr = NULL;
    // Update the AllocationCount to reflect the
    // dealloction of the Information structure
    AllocationCount--;
    // return a NULL because the list structure no longer exists
    return NULL;

}

/*
LL_AddAtFront is called to add the UserData as a node
to the front of the LinkedList whose "head" is identified
in the LinkedList Information structure LL_Ptr.

It gets a node filled with the UserData from local MakeNode
and links it into the list as the first node in the list.
Because it is the first node, it declares itself to be
the "head" in the information structure.  The number of
nodes in the list is updated to reflect the addition
of a node.

MakeNode adds increases allocation count by one to account for the
increase in malloc calls.
*/
void LL_AddAtFront (LLInfoPtr LLI_Ptr, UserData theData)
{
    // We should not have been called if the Linked List
    // Information structure does not exist, so make sure
    // it does and exit if not.
    assert (LLI_Ptr != NULL);
    // Make a node to place in the list
    // and place the node at the list start, updating
    // the head of the list and the linkage from the new
    // node to the next and prev nodes (if any)
    NodePtr NewNode = (NodePtr) MakeNode(theData);
    if (LLI_Ptr->Head != NULL) {
        LLI_Ptr->Head->prev = NewNode;
        NewNode->next = LLI_Ptr->Head;
    }
    // If the list is currently empty, then the new element
    // is the end of the list
    if (LLI_Ptr->NumNodesInList == 0)
        LLI_Ptr->Tail = NewNode;
    // The Node just allocated is now the Head of the LL
    LLI_Ptr->Head = NewNode;
    // update the number of nodes in the list to reflect
    // the addition of this node
    LLI_Ptr->NumNodesInList++;
    return;
}

/////////////
// LL_AddAtEnd is called to add the UserData as a node
// to the end of the LinkedList whose "Tail" is identified
// in the LinkedList Information structure LLI_Ptr.
// If there are no nodes currently in the list, it simply
// calls LL_AddAtFront to handle the situation.  Otherwise,
// it uses Tail and links the new node to the end, updating Tail
// and the links from / to the current "Tail".
// MakeNode adds increases allocation count by one to account for the
//increase in malloc calls.
/////////////

void LL_AddAtEnd (LLInfoPtr LLI_Ptr, UserData theData)
{
    // we should not have been called if the Linked List
    // Information structure does not exist, so make sure
    // it does and exit if not.
    assert (LLI_Ptr != NULL);
    // Given the structure exists, if there are no nodes,
    // just call LL_AddAtFront to add the data since "end"
    // is the same as the start.
    if (LLI_Ptr->Head == NULL)
        LL_AddAtFront(LLI_Ptr, theData);
    // Otherwise, make a Node and link it to the current Tail
    else {
        // make a node to insert and link it to the
        // current last node
        NodePtr NewNode = (NodePtr) MakeNode(theData);
        LLI_Ptr->Tail->next = NewNode;
        NewNode->prev = LLI_Ptr->Tail;
        // The new Tail is the Node just allocated
        LLI_Ptr->Tail = NewNode;
        // update the number of nodes in the list to reflect
        // the addition of this node
        LLI_Ptr->NumNodesInList++;
    }
}

/////////////
// LL_GetFront is called to return the user data at the front of the
// LL.  It verifies that (a) the underlying LL Information pointer exists,
// (b) there is a Node to extract the user data and (c) the caller has
// provided a valid choice to delete or retain the user data.  The program will
// abort if any of these conditions is not met.
/////////////
UserData LL_GetFront (LLInfoPtr LLI_Ptr, ShouldDelete Choice)
{
    // we should not have been called if the Linked List
    // Information structure does not exist, so make sure
    // it does and exit if not.
    // If it does exist, we also should not have been called
    // if there is no linked list in the structure, so exit
    // if there isn't one
    // Finally, makes sure the option to delete or retain is
    // provided, exiting if the option is illegal
    assert (LLI_Ptr != NULL);
    assert (LLI_Ptr->Head != NULL);
    assert (Choice == DELETE_NODE || Choice == RETAIN_NODE);
    // start by copying out the user data at the list start
    NodePtr top = LLI_Ptr->Head;
    UserData D = top->Data;
    // if the option was to delete the node, update the
    // new head information in the Information structure,
    // free the node just deleted and update the node count
    if (Choice == DELETE_NODE) {
        // update Head to point to the next node and deallocate the
        // current start of the LL
        LLI_Ptr->Head = top->next;
        top->prev = NULL;
        free (top);
        top = NULL;
        // because a node has been freed, update the
        // number of remaining nodes in the list
        LLI_Ptr->NumNodesInList--;
        // The head and tail are now set NULL if we have just deleted
        // the last of the nodes in the list
        if (LLI_Ptr->NumNodesInList == 0)
            LLI_Ptr->Head = LLI_Ptr->Tail = NULL;
        // because a node has been freed, update the
        // allocation count in the list
        AllocationCount--;
    }
    // return the user data that has been read from the start
    // of the linked list
    return D;
}

/////////////
// LL_Length returns the number of nodes in the underlying LL.
// It allows calls to be made even if the underlying LL does not
// exist, returning a count of zero under this condition
/////////////
int  LL_Length  (LLInfoPtr LLI_Ptr)
{
    // let's define the number of nodes to be zero
    // even if the information structure has not
    // been allocated. If it has been allocated,
    // return our running count of the nodes in the
    // list
    return (LLI_Ptr == NULL) ? 0 : LLI_Ptr->NumNodesInList;
}

/////////////
// LL_GetAtIndex returns the node user data at the specified index
// in the underlying LL.
// It calls GetNodeAddress to get the node address at the FetchIndex.
// Then return the data of that node.
/////////////
UserData  LL_GetAtIndex (LLInfoPtr LLI_Ptr, int FetchIndex)
{
    // Make sure the LL exists and the index is valid
    assert (LLI_Ptr != NULL);
    assert ((FetchIndex >= 0) && (FetchIndex < LLI_Ptr->NumNodesInList) );

    // call GetNodeAddress function to get the node pointer at UpdateIndex
    NodePtr getNode = GetNodeAddress(LLI_Ptr, FetchIndex);

// return it
return getNode->Data;
}

/////////////
// LL_SetAtIndex updates the node UserData at the specified index
// in the underlying LL.
// It calls getNodeAddress to get the node to update.
// The data is updated to what was provided by the caller.
/////////////
void  LL_SetAtIndex (LLInfoPtr LLI_Ptr, UserData D, int UpdateIndex)
{
    // Make sure the LL exists and the index is valid
    assert (LLI_Ptr != NULL);
    assert ((UpdateIndex >= 0) && (UpdateIndex < LLI_Ptr->NumNodesInList) );
    // call GetNodeAddress function to get the node pointer at UpdateIndex
    NodePtr toUpdate = GetNodeAddress(LLI_Ptr, UpdateIndex);

    // update node with desired data
    toUpdate->Data = D;
}

//////////////
// LL_Swap swaps the nodes at the specified indices Index1 and Index2
// in the underlying LL.
// It locates each node and then does a swap of the UserData in the nodes.
/////////////

void  LL_Swap (LLInfoPtr LLI_Ptr, int Index1, int Index2)
{
    // Make sure the LL exists and the index is valid
    assert (LLI_Ptr != NULL);
    assert ((Index1 >= 0) && (Index1 < LLI_Ptr->NumNodesInList) );
    assert ((Index2 >= 0) && (Index2 < LLI_Ptr->NumNodesInList) );
    // no need to do anything if the indices are the same
    if (Index1 == Index2)
        return;
    // get the node pointers for the two indices
    NodePtr Index1DataPtr = GetNodeAddress(LLI_Ptr, Index1);
    NodePtr Index2DataPtr = GetNodeAddress(LLI_Ptr, Index2);
    // using the pointers, swap their data
    UserData temp = Index1DataPtr->Data;
    Index1DataPtr->Data = Index2DataPtr->Data;
    Index2DataPtr->Data = temp;
    return;
}

/////////////
// Local function MakeNode allocates and initializes a Node for placement
// in the LL.  It copies over the user data into the allocated node and NULLs the
// node's "next" link.
/////////////
NodePtr MakeNode (UserData theData)
{
    // allocate a node to contain the user's data
    // and abort if the allocation fails
    NodePtr NewNode = (NodePtr) malloc (sizeof (Node));
    assert (NewNode != NULL);
    // allocation worked, copy in the user data without
    // copying field by field.
    NewNode->Data = theData;
    // unless updated by the caller of MakeNode, the "next"
    // and "prev" default to NULL
    NewNode->next = NULL;
    NewNode->prev = NULL;
    // Update the number of allocations to reflect the malloc
    AllocationCount++;
    // return the pointer to the node ready to link in
    return NewNode;
}

/////////////
// GetNodeAddress is a utility function that will locate
// the node at Index and return its address.
// The function first calculates the middle of the Linked List
// then based on the given FetchIndex will either look for the node
// forwards or backwards.
// Once the position in the LL has been reached, the node address
// is returned.
/////////////
NodePtr GetNodeAddress (LLInfoPtr LLI_Ptr, int FetchIndex)
{
    // Make sure the LL exists and the index is valid
    assert (LLI_Ptr != NULL);
    assert ((FetchIndex >= 0) && (FetchIndex < LLI_Ptr->NumNodesInList) );

    // Calculate the middle of the Linked List given the current node size
    int middle = LLI_Ptr->NumNodesInList / 2;

    // A variable to store the current node pointer
    NodePtr curr;

    // If the fetch index is less than or equal to the middle,
    // Start searching from the Head and work your way up toward the middle.
    // Stops once i == FetchIndex - 1, or i < FetchIndex, meaning curr now points to the correct node!
    if (FetchIndex <= middle) {
        // set curr to the Head of the list
        curr = LLI_Ptr->Head;
        for (int i = 0; i < FetchIndex; i++) {
            curr = curr->next;
        }
    } else {
        // Else, if the fetch index is greater than the middle,
        // Start searching from the Tail and work your way down toward the middle.
        curr = LLI_Ptr->Tail;
        for (int i = LLI_Ptr->NumNodesInList - 1; i > FetchIndex; i--) {
            curr = curr->prev;
        }
    }

    // return its UserData
    return curr;
}
