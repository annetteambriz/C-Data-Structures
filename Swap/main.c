#include <stdio.h>
#include <stdlib.h> // for use of malloc

/****************************************************
A structure to hold two integers
*****************************************************/

typedef struct {
    int intOne;
    int intTwo;
} TwoInts;

// Function prototypes
void swapStructs(TwoInts *structOne, TwoInts *structTwo);
void swap(int *intOne, int *intTwo);

/****************************************************
Function: swap
Summary:
swap is a function that swaps to given integers.
Integers are passed by reference so the value of
the calling variables are swapped.

Parameters:
    intOne - an integer
    intTwo - an integer

Returns:
    void

*****************************************************/

void swap(int* intOne, int* intTwo) {

    // create a temp variable to store the value of intOne
    int temp = *intOne;

    // swap intOne with IntTwo
    *intOne = *intTwo;

    // assign the previous value of intOne to intTwo
    *intTwo = temp;
}

/****************************************************
Function: swapStructs
Summary:
swapStructs is a function that swaps the values in a given
TwoInts struct.
Structs are passed by reference so the value of
the calling structs are swapped.

Parameters:
    structOne - an TwoInts struct
    structTwo - an TwoInts struct

Returns:
    void

*****************************************************/

void swapStructs(TwoInts *structOne, TwoInts *structTwo) {

    // store the values of struct one to a temp variable
    int temp1 = structOne->intOne;

    // swap values in struct one with the values of struct two
    structOne->intOne = structTwo->intTwo;

    // assign the value of struct two with the previous values
    // of struct one
    structTwo->intTwo = temp1;
}

int main(void) {
    // declare two integers and initialize them to the values 1 and -1
    int one = 1, two = -1;

    // print out the integers
    printf("Before swap: \n");
    printf("Variable One: %d\n", one);
    printf("Variable Two: %d\n", two);

    // call swap
    swap(&one, &two);

    // print out the values after swap is called
    printf("After swap: \n");
    printf("Variable One: %d\n", one);
    printf("Variable Two: %d\n", two);

    // Dynamically allocate memory for two separate structs
    TwoInts *structOne = malloc(sizeof(TwoInts));
    TwoInts *structTwo = malloc(sizeof(TwoInts));

    // filling the first with the values 10 and 20 and the second with 30 and 40
    *structOne = (TwoInts){10, 20};
    *structTwo = (TwoInts){30, 40};

    // print structs before swap
    printf("Before swapStructs: \n");
    printf("Struct One: %d %d\n", structOne->intOne, structOne->intTwo);
    printf("Struct Two: %d %d\n", structTwo->intOne, structTwo->intTwo);

    // call swapStructs
    swapStructs(structOne, structTwo);

    // print structs after swap
    printf("After swapStructs: \n");
    printf("Struct One: %d %d\n", structOne->intOne, structOne->intTwo);
    printf("Struct Two: %d %d\n", structTwo->intOne, structTwo->intTwo);

    // free allocated memory to prevent memory leaks
    free(structOne);
    free(structTwo);
    return 0;
}