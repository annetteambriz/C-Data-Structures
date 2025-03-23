/*
 * Program P5.1 from Kalicharan, modified to make it easier to document and understand.
 * It uses recursive implementations of pre, in and post order traversals.
 *
 * An additional modification is the addition of the parent linkage that can be used to
 * traverse from a node back through its parent.
 *
 *
 * <<< what a recursive routine is
 * A recursive function or routine is a function that calls itself to complete a task.
 * The function has a base case that is the condition for the termination of the recursive calls.
 *
 * <<< You need to add your program description here, including
 * The program implementation below uses recursion to traverse a trees' nodes in
 * preorder, inorder, postorder. This is done by the functions calling themselves until the condition
 * nodeP != NULL is found, which indicates that all the nodes have been traversed.
 *
 */


 /*
 * <<< What are these includes?  What does each of them provide?
 * <<< an easy way to learn is to comment out one and see what
 * <<< the compiler warnings and errors tell you
*/
#include <stdio.h> // provides the functions for i/o, printf, fopen and fscanf
#include <string.h> // provides the strcmp and strcpy functions
#include <stdlib.h> // provides the functions for memory management, malloc and free

// <<< you need to add comments on what these are and how they
// <<< are used
// These constants are defined at a preprocessor level
// Defines a char limit size for the number of char in a word stored in a node
#define MaxWordSize 20
// Defines a constant for the file name used to read in word data
#define FILENAME "btree.in" // Input data file for tree

// An enum used in the getRelativeWord function to
// generalize finding a relatives' word data
typedef enum {
    PARENT,
    LEFT,
    RIGHT
} Relative;

// <<< what are these 3 typedefs?  what do they contain??  how are they used??
// <<< why is "word" set to MaxWorkSize+1?

/*
 * This data structure is used to define the structure of the data stored in a TreeNode.
 * Called NodeData, it has a single char array called word that stores at most MaxWordSize (20)
 * plus 1, (likely used for null terminating char).
 */
typedef struct {
    char word[MaxWordSize+1];
} NodeData;

/*
 * This data structure is used to define the structure stored in the BinaryTree.
 * Called TreeNode, it also has a pointer reference called TreeNodePtr for faster accesses.
 * It has two fields, one called data, which is a NodeData struct, and three pointers to other treeNodes.
 * These pointers represent possible right and left children nodes, and the parent node.
 * It's important to note that these three pointers are self-referential or recursive-like in nature since we are
 * in the definition of the treeNode itself.
 * This does not lead to an infinite loop or infinite memory usage because these are only pointers to other treeNode
 * references and dynamic memory allocation is used for those structures.
 */
typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right, *parent;
} TreeNode, *TreeNodePtr;

/*
 * This is a struct used to represent a Binary tree.
 * Because all nodes reference their children nodes and parent nodes, only the start of the tree
 * or the root of the tree is needed to access the rest of the tree. Very elegant.
 * Only the parent node of the root node should be null.
 */
typedef struct {
    TreeNodePtr root;
} BinaryTree;

// To make sure we are allocating and deallocating dynamic memory,
// variable AllocationCount is declared within the BinaryTree code.
// It could be referenced by any other code that does dynamic memory
// allocation and deallocation if we needed using extern
int AllocationCount = 0;

// The declarations for all the called functions are here
// <<< you must add comments on what they are and how they contribute
// <<< to the problem solution

/*
 * Function declarations.
 * buildTree - uses a file passed via a pointer to create a tree structure using the data in the file.
 *              A pointer reference to the current node being created is passed in called nodeParent.
 * preOrder - traverse tree in pre-order
 * inOrder - traverse the tree in-order
 * postOrder - traverse tree in post order
 * visit - Takes a TreeNodePtr and prints the NodeData word array.
 * postOrderNodeDump - Traverses the tree in post order to dump all the word data of the tree.
 * deleteTree - Traverses the tree in post-order and deletes the nodes as it traverses them.
 * visitAll - Takes a TreeNodePtr and prints the NodeData word for each relative of the the TreeNodePtr.
 *             Traverse the whole tree in post-order.
 * getRelativeWord - Takes a TreeNodePtr and returns pointer to the relative's word, or "*" if the relative
 *                    does not exist or the word is NULL.
 */
TreeNodePtr buildTree         (FILE * in, TreeNodePtr nodeParent);
void        preOrder          (TreeNodePtr nodeP);
void        inOrder           (TreeNodePtr nodeP);
void        postOrder         (TreeNodePtr nodeP);
void        visit             (TreeNodePtr nodeP);
void        postOrderNodeDump (TreeNodePtr nodeP);
TreeNodePtr deleteTree        (TreeNodePtr nodeP);
void        visitAll          (TreeNodePtr nodeP);
char        *getRelativeWord  (TreeNodePtr nodeP, Relative rel);

// entry point
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns

/**
 *
 * A main function to test the tree functions.
 * Attempts to open a file and if successful, instantiates a binary tree and
 * calls buildTree to create a tree with the file data.
 * We then call preOrder, inOrder, postOrder, printing the tree out in each step.
 * The visit() function, which is called by the functions listed above, prints the nodes
 * at each step.
 */
int main()
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses

    // Attempt to open the file
    // If the returned pointer is NULL exit, unsuccessful.
    FILE * in = fopen(FILENAME, "r");
    if (in == NULL) {
        printf ("Unable to open file %s... exiting\n", FILENAME);
        exit (0);
    }
    // If successful, create a BinaryTree struct
    BinaryTree bt;

    printf("Starting Binary Tree Demo... \n");
    printf ("\nCurrent number of allocations: ""%d", AllocationCount);

    printf("\nBuilding tree... ");
    // build a tree and assign the reference to the tree to our BinaryTree root field
    bt.root = buildTree(in, NULL);
    printf ("\nCurrent number of allocations after tree is built: ""%d", AllocationCount);

    printf("\n\nThe pre-order traversal is: ");
    // traverse the tree in preorder
    preOrder(bt.root);
    printf("\nThe in-order traversal is: ");
    // traverse the tree inorder
    inOrder(bt.root);
    printf("\nThe post-order traversal is: ");
    // traverse the tree in postorder
    postOrder(bt.root);
    // <<< In problem 4, your header for the table showing the node name,
    // <<< parent, left child, right child, left sibling and right sibling
    // <<< will be done here
    // <<< printf (.....)
    // <<< In problem 4, you will make the call to postOrderNodeDump
    printf("\n\nPrinting node dump in post order...");
    printf("\n\n%-10s %-10s %-10s %-10s %-10s %-10s\n",
       "Node", "Parent", "LChild", "RChild", "LSib", "RSib");
    postOrderNodeDump(bt.root);

    printf("\n\nStarting deletion of the tree in post order...");
    // delete the tree at the end to free up dynamically allocated memory
    bt.root = deleteTree(bt.root); // delete tree and set root to NULL
    printf ("\n\nNumber of allocations after deletion: ""%d", AllocationCount);

    printf("\nThe in-order traversal is now: ");
    inOrder(bt.root);
    printf("\n\n");
    // close the opened file
    fclose(in);
} // end main

// buildTree
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns

/**
 *
 * Recursively calls buildTree to build a tree using an input file
 * and a TreeNodePtr which is the current node parent. Recursive calls are
 * used to create the children of the tree. An "@" char is used to signify a
 * terminal node.
 * @param in - Input file pointer
 * @param nodeParent - The node for which we are building its children nodes.
 * @return - the TreeNodePtr of the current node, whose possible children where built.
 */
TreeNodePtr buildTree   (FILE * in, TreeNodePtr nodeParent)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses

    // create a char array of MaxWordSize+1 size to pass into the fscanf function
    char str[MaxWordSize+1];
    // scan in a char and store it in str array
    fscanf(in, "%s", str);

    // if the char is a @ symbol, then return NULL, the node has no children, is terminal
    if (strcmp(str, "@") == 0) return NULL;
    // else allocate memory dynamically for a new TreeNode and assign the memory pointer to a TreeNodePtr
    TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
    // increment allocation count since malloc was used
    AllocationCount ++;
    // copy the current char to the newly created TreeNode's data word field
    strcpy(p -> data.word, str);
    // assign the parent node pointer to the nodeParent that was passed into the function
    p -> parent = nodeParent;
    // call buildTree again, and pass in the current node pointer as the new nodeParent in the function call.
    // when the function call stack completes, the returned TreeNodePtr will be assigned to this node's left child
    // treeNode pointer.
    // run again for the right child treeNode.
    p -> left = buildTree(in, p);
    p -> right = buildTree(in, p);
    // return this TreeNodePtr
    return p;
} //end buildTree

// visit
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns
/**
 * Takes a TreeNodePtr and prints the NodeData word array.
 * In other words, the word stored as data for that node.
 *
 * @param nodeP
 */
void visit(TreeNodePtr nodeP)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses
    // Using the TreeNodePtr pointer, access the TreeNode structs' NodeData
    // field to access the word array. Prints as a string.
    printf("%s ", nodeP -> data.word);
} //end visit

/**
 * A helper function that returns the word stored in a relative
 * node of the given TreeNodePtr.
 * @param nodeP - a TreeNodePtr to the current tree node.
 * @param rel - a Relative enum indicating which relative to access
 * @return - A pointer to the relative's word, or "*" if the relative
 *           does not exist or the word is NULL.
 */
char *getRelativeWord(TreeNodePtr nodeP, Relative rel) {
    // if nodeP is not null access relative, otherwise return "*"
    if (nodeP != NULL) {
        // variable to store relative
        TreeNodePtr relative = NULL;

        // check enum for which relative to access
        switch (rel) {
            case PARENT:
                relative = nodeP -> parent;
                break;
            case LEFT:
                relative = nodeP -> left;
                break;
            case RIGHT:
                relative = nodeP -> right;
                break;
            default:
                // invalid input will just return *
                return "*";
        }
        // if relative exists return relative's word data
        if (relative != NULL) {
            return relative->data.word;
        }
        // otherwise return "*"
        return "*";
    }
    return "*";
} //end getRelativeWord

/**
 * Takes a TreeNodePtr and prints the
 * following relative to that TreeNodePtr
 * if null prints '*':
 * The node's parent
 * The node's left child
 * The node's right child
 * The node's left sibling
 * The node's right sibling
 *
 * @param nodeP
 */
void visitAll(TreeNodePtr nodeP)
{
    // Using the TreeNodePtr pointer, access the TreeNode structs' relatives
    // Prints relatives' word data as a string.
    // Access the current nodes' word and store in a pointer variable.
    // If the node does not exist, set variable to "*"
    // Either the left or right sibling should be null depending on the current node.

    // local variables
    char *currentNode;
    char *parent;
    char *leftChild;
    char *rightChild;
    char *leftSibling;
    char *rightSibling;

    // get current node's word
    currentNode = nodeP->data.word;
    // get relative word data
    parent = getRelativeWord(nodeP, PARENT);
    leftChild = getRelativeWord(nodeP, LEFT);
    rightChild = getRelativeWord(nodeP, RIGHT);

    // Find left sibling by finding parent's left child
    if (nodeP->parent != NULL && nodeP->parent->left != NULL && nodeP->parent->left != nodeP) {
        leftSibling = nodeP->parent->left->data.word;
    } else leftSibling = "*";

    // Find the right sibling by finding parent's right child
    if (nodeP->parent != NULL && nodeP->parent->right != NULL && nodeP->parent->right != nodeP) {
        rightSibling = nodeP->parent->right->data.word;
    } else rightSibling = "*";

    // print out nodes' relatives data
    printf("%-10s %-10s %-10s %-10s %-10s %-10s\n",
           currentNode, parent, leftChild, rightChild, leftSibling, rightSibling);
} //end visitAll

// preOrder
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns

/**
 * Using a TreeNodePtr, this function traverses the nodes in a tree
 * in post-order.
 * Calls the visit function to print out the current nodes'
 * word data.
 *
 * @param nodeP
 */
void preOrder(TreeNodePtr nodeP)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses
    //If the current node pointer is not null
    if (nodeP != NULL) {
        // "visit" or print out the parent node first, starting with the
        // root node
        visit(nodeP);
        // then recursively traverse the tree visiting all the left most children
        // until a terminal leaf node is found.
        preOrder(nodeP -> left);
        // then recursively visit all the right children.
        // if a terminal leaf node is found, recursive call "collapses" back
        // to the previous parent node. I.e., backtrack when there are no more nodes to process.
        preOrder(nodeP -> right);
    }
} //end preOrder

// inOrder
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns

/**
 * This function traverses the nodes in-order recursively.
 * Calls the visit function to print out the current nodes' word data.
 * @param nodeP
 */
void inOrder(TreeNodePtr nodeP)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses
    if (nodeP != NULL) {
        // recursively traverse the tree to the leftmost node
        // until a terminal leaf node is found.
        inOrder(nodeP -> left);
        // "visit" or print out the current node when the leftmost subtree has been
        // traversed
        visit(nodeP);
        // then recursively visit the right subtree/children.
        // backtrack when there are no more nodes to process.
        inOrder(nodeP -> right);
    }
} //end inOrder

// postOrder
// <<< you need to add a description of what this does, including
// <<< any inputs it gets and what it returns
/**
 * This function traverses the nodes in post order recursively.
 * Calls the visit function to print out the current nodes' word data.
 *
 * @param nodeP
 */
void postOrder(TreeNodePtr nodeP)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses

        // if the current node pointer is not null
        if (nodeP != NULL) {
        // recursively traverse the left children of the tree
        postOrder(nodeP -> left);
        // then recursively visit the right subtree
        postOrder(nodeP -> right);\
        //visit the current node only after both the left and right subtrees have
        //been processed. Backtrack after this step and when
        //there are no more nodes to process.
        visit(nodeP);
    }
} //end postOrder

// postOrderNodeDump - used in Problem 4 to print out
// a node's name, parent, left and right children and left and right
// siblings
/**
 *  Traverses nodes in post order and calls funciton visitAll to
 *  print out relatives of the node.
 * @param nodeP
 */
void postOrderNodeDump (TreeNodePtr nodeP)
{
// <<< each logically grouped set of statements must be documented
// <<< to state what it does and what data it declares and uses
    if (nodeP != NULL) {
        postOrderNodeDump (nodeP -> left);
        postOrderNodeDump (nodeP -> right);
        visitAll(nodeP);
    }

} //end postOrderNodeDump


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
        printf("\nDeleting node: %s", nodeP->data.word);
        // free memory for the TreeNode
        free(nodeP);
        // decrement AllocationCount
        AllocationCount --;
        return NULL;
    }
    return NULL;
}