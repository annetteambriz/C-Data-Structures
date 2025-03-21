//
//  main.c
//
#include <stdio.h>
#include <stdlib.h>

/****************************************************
 Program PingPong is designed to demonstrate functions
 which call each other until a condition is met.
 It is a demonstration of recursion.
 Function Ping starts the process, receiving an integer from the test Main.
 It will call Pong with the integer reduced by one if the integer is positive.
 Pong will reduce the integer and call Ping if the number is positive.
 *****************************************************/

#include "PingPong.h"
#include <stdio.h>

// the test main executes the PingPong processing for 5 iterations.
int main()
{
    // bounce 10 times before returning
    int loop = 5;
    printf ("Kicking off the PingPong for %d iterations\n", loop);
    // kick off PingPong
    Ping (loop);
    printf ("Back from the PingPong iterations.\n");
    return 0;
}

