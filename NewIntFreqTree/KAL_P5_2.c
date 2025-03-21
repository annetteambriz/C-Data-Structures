// Program P5.2 from Kalicharan, reformatted and ready for documentation and modification
//
// The program demonstrates how to form a BST and display it.  It uses a file containing
// integers as the input and the BST is formed from the integers.  Each integer has
// an occurrence frequency, which is incremented whenever the identical integer is
// found in the file.
//
// After creating the BST, it is traversed and the output is written into a file.

// The traversal done is an in-order.  When done against a BST, it will execute
// visits in a sorted manner!  That's why the file produced has the integers in incrementing
// order.
// If you don't believe it, change the file statement "if (cmp < 0)" in
// function findOrInsert to "if (cmp > 0)" and rerun the program.  You will see
// that the tree now runs in decrementing order!


// stdio provides access to file processing and console processing
#include <stdio.h>
// string provides the string functions
// strcmp -
//      returns a negative number if the first string < second string,
//      0 if they are equal
//      and a number > 0 if the first string > second string
#include <string.h>
// stdlib provides malloc and free dynamic memory allocations
#include <stdlib.h>
// ctype gives us the following
// isalpha - looks at a character and returns 0 if it is not an alphanumeric
//           and non 0 if it is
// tolower - returns a lower case version of a character (eg. A becomes a)
#include <ctype.h>

// stdbool defines "bool", "true" and "false"
// it is used whenever a boolean is being produced, used, or passed back to a caller
#include <stdbool.h>

// <<< you need to describe what each of these is and how it is used in the solution
#define MaxIntSize 20
#define INFILENAME "integers.in"
#define OUTFILENAME "integersFreq.out"

// <<< you need to describe what each of these is and how they are used in the solution
typedef struct {
    int integer;
    int freq;
} NodeData;

typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right;
} TreeNode, *TreeNodePtr;

typedef struct {
    TreeNodePtr root;
} BinaryTree;

// declarations of all the local functions

// getInt is a utility that reads integers from a file to
// can have negative numbers
bool        getInt     (FILE *, int * integer);

// newTreeNode dynamically allocated a tree node, fills
// in the user data and clears the left and right side links
TreeNodePtr newTreeNode (NodeData nodeInformation);

// newNodeData is a utility that packages an integer and a frequency
// into a user data struct called NodeData
NodeData    newNodeData (int anInteger, int frequency);

// findOrInsert traverses a binary search tree looking for a node
// that matches the user criteria.  In this case, it is an integer.
// It either returns the pointer to the matching node,
// or it links the node into the tree at its proper, sorted location
TreeNodePtr findOrInsert(BinaryTree, NodeData nodeInformation);

// inOrder does a traversal of the BST that will write a file
// with the traversal results.
void        inOrder     (FILE *, TreeNodePtr);

// a helper function to compare two integers
// return -1 if x is smaller than y, 1 if x is greater than y
// and returns 0 if they are equal
int compareIntegers (int x, int y);

TreeNodePtr deleteTree         (TreeNodePtr nodeP);

// To make sure we are allocating and deallocating dynamic memory,
// variable AllocationCount is declared within the BinaryTree code.
// It could be referenced by any other code that does dynamic memory
// allocation and deallocation if we needed using extern
int AllocationCount = 0;

// main will do the following:
//      1. It opens both an input and output file. Failure to be able to
//          open the files will result in program termination
//      2. It will build a BST from the file integers and maintain a
//          count of the number of occurrences of each integer
//      3. It will write the integers and their occurrences in a file
int main()
{
    // integer is a scratch variable used to get complete integers from the file
    int integer;

    // open the input file and exit if it does not open
    FILE * in = fopen( INFILENAME, "r");
    if (in == NULL) {
        printf ("Unable to open file %s... exiting", INFILENAME);
        exit (0);
    }

    // the input file opened, so open the output file.
    // it does not open, close the input file and exit
    FILE * out = fopen( OUTFILENAME, "w");
    if (out == NULL)
    {
        printf ("Unable to open file %s for output... exiting", OUTFILENAME);
        fclose (in);
        exit(0);
    }

    printf ("\nCurrent number of allocations: ""%d\n", AllocationCount);

    // both files are open, declare the binary search tree (bst)
    // and initialize its root as NULL
    BinaryTree bst;
    bst.root = NULL;

    // get int and insert them into the BST.
    // since new nodes will have a frequency of 0 and matching
    // nodes will have a current frequency, bump the frequency
    // in either case to reflect their occurrence in the text
    printf("\nBuilding tree... ");
    while (getInt(in, &integer)) {
        if (bst.root == NULL)
            bst.root = newTreeNode(newNodeData(integer, 1));
        else {
            TreeNodePtr node = findOrInsert(bst, newNodeData(integer, 0));
            node->data.freq++;
        }
    }

    printf ("\n\nCurrent number of allocations after tree built: ""%d\n", AllocationCount);
    // The file has been processed.  Write out the results by using
    // an in-order traversal and writing as the "visit"
    fprintf(out, "\nIntegers        Frequency\n\n");
    inOrder(out, bst.root);
    fprintf(out, "\n\n");

    printf("\nDeleting the tree in post-order: ");
    // delete the tree at the end to free up dynamically allocated memory
    bst.root = deleteTree(bst.root); // delete tree and set root to NULL
    printf ("\n\nNumber of allocations after deletion: ""%d\n", AllocationCount);

    // close both files and return.  We're done!!
    fclose(in);
    fclose(out);
    return 0;
} // end main

// getInt has the task of reading in single integers from the file
// The routine returns true if there is an integer and false if there is none
//
bool getInt(FILE * in, int * integer)
{
    // Attempt to read an integer from the file
    int result = fscanf(in, "%d", integer);

    //  if the read was successful
    if (result == 1) {
        return true; // Successfully read an integer
    }
    return false; // Failed to read an integer
} // end getInt

// findOrInsert searches a binary tree looking for nodeInformation
// in this implementation, the nodeInformation field "integer" is being
// looked at to see if there is a match.
//
// Because this is a binary tree, we can keep comparing if the
// value is less than us (indicating to proceed left), is us, or
// greater than us (indicating to proceed right).
// If we hit the end of a left traversal and the value has not been found,
// we add it to our left side and return it
// In a similar manner if we hit the end of a right traversal and the
// value has not been found, we add it to the right side and return it
// the node we return will either be a new node (zero frequency) or a node
// that we have found.  That enables the caller to increment the frequency
// without knowing if this was a new node or a match

TreeNodePtr findOrInsert(BinaryTree bt, NodeData nodeInformation)
{
    // if the root is empty, just return a node with the nodeInformation in it
    if (bt.root == NULL) return newTreeNode(nodeInformation);

    // curr is the tree node currently at the top of the tree
    TreeNodePtr curr = bt.root;
    // since strcmp returns an integer (neg, zero, or pos) save in cmp
    int cmp;
    // loop until we have a match (returns in the loop will happen if
    // we hit the end of the tree
    while ((cmp = compareIntegers(nodeInformation.integer, curr -> data.integer)) != 0) {
        // are we less than the node?
        if (cmp < 0) {
            // yes, need to go left if we can
            // NULL indicates we are at a left leaf, so add the new node
            // to the current leaf on the left side and return it
            if (curr -> left == NULL)
                return curr -> left = newTreeNode(nodeInformation);
            else
                // keep looking left since we are not at a leaf
                curr = curr -> left;
        } else {
            // compareIntegers said we are greater than the current right side
            // need to go further right if we can
            // NULL indicates we are at a right leaf, so add the new node
            // to the current leaf on the right side and return it
            if (curr -> right == NULL)
                return curr -> right = newTreeNode(nodeInformation);
            else
                // keep looking right since we are not at a leaf
                curr = curr -> right;
        }
    }
    // we get here if the while completed, indicating we found a node
    // that matched a current node in the tree
    // return pointer to the node
    return curr;
} //end findOrInsert

// newTreeNode makes a node through dynamic allocation, initializing
// its left and right children to NULL and inserting the user data provided
// as nodeInformation.
// It returns the pointer to the tree node it just allocated and initialized
TreeNodePtr newTreeNode(NodeData nodeInformation)
{
    // allocate a tree node
    TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
    // fill in the user data
    p -> data = nodeInformation;
    // NULL its links
    p -> left = p -> right = NULL;
    // increase allocation count for new node
    AllocationCount ++;
    // give it back to the caller
    return p;
} //end newTreeNode

// inOrder does a go left, visit, go right traversal through recursively
// calling itself.  Instead of calling on a "visit", it accomplishes it
// by writing out the user data integer and occurrence count to the file
// provided
void inOrder(FILE * out, TreeNodePtr node)
{
    // if we are not NULL we cannot go further in the tree
    if (node!= NULL) {
        // go left
        inOrder(out, node -> left);
        // "visit" by printing the user information
        fprintf(out, "%8d %10d\n", node->data.integer, node->data.freq);
        // go right
        inOrder(out, node -> right);
    }
} //end inOrder

// newNodeData is a utility that builds a NodeData structure from
// the user data fields it receives as input.  In this case, it is an integer
// that is NULL terminated and an initial frequency of occurrence
NodeData newNodeData(int anInteger, int frequency)
{
    // make a NodeData and fill it with the integer and frequency provided
    NodeData temp;

    // set the integer and frequency values
    temp.integer = anInteger;
    temp.freq = frequency;
    // return it with the packaging of the user data complete
    return temp;
} //end newNodeData

/**
 * compareIntegers is a small helper function
 * to compare to integers.
 * @param x - an integer
 * @param y - another integer to compare against x
 * @return - returns 1 if x is greater than y and
 *           returns -1 if x is smaller than y.
 *           returns 0 if they are equal.
 */
int compareIntegers(int x, int y) {
    // if x is smaller than y return -1
    if (x < y) return -1;
    // else if x is greater than y return 1
    if (x > y) return 1;
    // return 0 if they are equal
    return 0;
}

/**
 * Recursively delete all nodes in a binary tree.
 * Processed in post-order, with the left child deleted, then the right child,
 * then the parent node deleted.
 * @param nodeP - parent node pointer
 */
TreeNodePtr deleteTree(TreeNodePtr nodeP) {
    if (nodeP != NULL) {
        // recursively call deleteTree for the left and right child nodes
        deleteTree(nodeP -> left);
        deleteTree(nodeP -> right);

        // print node data before deleting it
        printf("\n\nDeleting node for integer: %d", nodeP->data.integer);
        // free memory for the TreeNode
        free(nodeP);
        // decrement AllocationCount
        AllocationCount --;
        return NULL;
    }
    return NULL;
}