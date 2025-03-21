// Program P5.2 from Kalicharan, reformatted and ready for documentation  and modification
//
// The program demonstrates how to form a BST and display it.  It uses a file containing
// text as the input and the BST is formed from the words.  Each word has
// an occurrence frequency, which is incremented whenever the identical word is
// found in the file.
//
// After creating the BST, it is traversed and the output is written into a file.

// The traversal done is an in-order.  When done against a BST, it will execute
// visits in a sorted manner!  That's why the file produced has the words from a-z.
// If you don't believe it, change the file statement "if (cmp < 0)" in
// function findOrInsert to "if (cmp > 0)" and rerun the program.  You will see
// that the tree now runs from z-a!


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
#define MaxWordSize 20
#define INFILENAME "wordFreq.in"
#define OUTFILENAME "wordFreq.out"

// <<< you need to describe what each of these is and how they are used in the solution
typedef struct {
    char word[MaxWordSize+1];
    int freq;
} NodeData;

typedef struct treeNode {
    NodeData data;
    struct treeNode *left, *right;
} TreeNode, *TreeNodePtr;

typedef struct {
    TreeNodePtr root;
} BinaryTree;

// declarations of all of the local functions

// getWord is a utility that reads characters from a file to
// form a word.  It skips over leading spaces, building a character
// at a time because the input is actually a file containing
// what may be multiple words on each file line
bool        getWord     (FILE *, char aWord[] );

// newTreeNode dynamically allocated a tree node, fills
// in the user data and clears the left and right side links
TreeNodePtr newTreeNode (NodeData nodeInformation);

// newNodeData is a utility that packages a word and a frequency
// into a user data struct called NodeData
NodeData    newNodeData (char aWord[], int frequency);

// findOrInsert traverses a binary search tree looking for a node
// that matches the user criteris.  In this case, it is a word.
// It either returns the pointer to the matching node
// or it links the node into the tree at its proper, sorted location
TreeNodePtr findOrInsert(BinaryTree, NodeData nodeInformation);

// inOrder does a traversal of the BST that will write a file
// with the traversal results.
void        inOrder     (FILE *, TreeNodePtr);

// main will do the following:
//      1. It opens both an inut and output file.  Failure to be able to
//          open the files will result in program termination
//      2. It will build a BST from the file words and maintain a
//          count of the number of occurrences of each word
//      3. It will write the words and their occurrences in a file
int main()
{
    // word is a scratch array used to get complete words from the file
    char word[MaxWordSize+1];

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

    // both files are open, declare the binary search tree (bst)
    // and initialize its root as NULL
    BinaryTree bst;
    bst.root = NULL;

    // get words and insert them into the BST.
    // since new nodes will have a frequency of 0 and matching
    // nodes will have a current frequency, bump the frequency
    // in either case to reflect their occurrence in the text
    while (getWord(in, word) == true) {
        if (bst.root == NULL)
            bst.root = newTreeNode(newNodeData(word, 1));
        else {
            TreeNodePtr node = findOrInsert(bst, newNodeData(word, 0));
            node -> data.freq++;
        }
    }

    // The file has been processed.  Write out the results by using
    // an in-order traversal and writing as the "visit"
    fprintf(out, "\nWords        Frequency\n\n");
    inOrder(out, bst.root);
    fprintf(out, "\n\n");

    // close both files and return.  We're done!!
    fclose(in);
    fclose(out);
    return 0;
} // end main

// getWord has the task of reading in single characters from
// the file, constructing a character string (NULL terminated)
// and an indication if it was able to build a word.
// It skips over leading spaces and builds a word from the first
// character it sees until it hits a space or end of file.
//
// The user provides an array to place the word in.
// The routine returns true if there is a word and false if there is none
//
bool getWord(FILE * in, char aWord[])
{
    // ch is the holding area for a character
    char ch;
    // n is the index into aWord that will next be filled with a character
    int n = 0;
    // read over non-letters
    while (!isalpha(ch = getc(in)) && ch != EOF) ; //empty while body
    // if we see an end of file while looking for the first character,
    // return false to indicate no word is present
    if (ch == EOF) return false;
    // add the character (in lower case) to the word
    aWord[n++] = tolower(ch);
    // now keep adding unless we are either at the allowed size
    // of the user array or we have an end of file
    while (isalpha(ch = getc(in)) && ch != EOF)
        if (n < MaxWordSize) aWord[n++] = tolower(ch);
    // we are either at the end of file or have found a space
    // terminate the user array with a NULL so string functions can be used with it
    aWord[n] = '\0';
    // return indication that a word is present in aWord
    return true;
} // end getWord

// findOrInsert searches a binary tree looking for nodeInformation
// in this implementation, the nodeInformation field "word" is being
// looked at to see if there is a match.
//
// Because this is a binary tree, we can keep comparing if the
// value is less than us (indicating to proceed left), is us, or
// greater than us (indicating to proceed right).
// If we hit the end of a left traversal and the value has not been found,
// we add it to our left side and return it
// In a similar manner, if we hit the end of a right traversal and the
// value has not been found, we add it to the right side and return it
// the node we return will either be a new node (zero frequency) or a node
// that we have found.  That enables the caller to increment the frequency
// without knowing if this was a new node or a match
//
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
    while ((cmp = strcmp(nodeInformation.word, curr -> data.word)) != 0) {
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
            // strcmp said we are greater than the current right side
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
    // give it back to the caller
    return p;
} //end newTreeNode

// inOrder does a go left, visit, go right traversal through recursively
// calling itself.  Instead of calling on a "visit", it accomplishes it
// by writing out the user data word and occurrence count to the file
// provided
void inOrder(FILE * out, TreeNodePtr node)
{
    // if we are not NULL we cannot go further in the tree
    if (node!= NULL) {
        // go left
        inOrder(out, node -> left);
        // "visit" by printing the user information
        fprintf(out, "%-15s %2d\n", node -> data.word, node -> data.freq);
        // go right
        inOrder(out, node -> right);
    }
    return;
} //end inOrder

// newNodeData is a utility that builds a NodeData structure from
// the user data fields it receives as input.  In this case, it is a word
// that is NULL terminated and an initial frequency of occurrence
NodeData newNodeData(char aWord[], int frequency)
{
    // make a NodeData and fill it with the word and frequency provided
    NodeData temp;
    strcpy(temp.word, aWord);
    temp.freq = frequency;
    // return it with the packaging of the user data complete
    return temp;
} //end newNodeData

