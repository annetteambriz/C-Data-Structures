//
//  PingPong.c
//

#include "PingPong.h"
#include <stdio.h>

/****************************************************
 Function: Ping
 Summary:
 Ping is responsible for logging its received value (val) and conditionally calling Pong.
 After logging the received input, it passes the information to Pong with the input
 value decremented by 1 if the input was positive.

 When the function returns, it provides an int with the decremented value
 *****************************************************/
int Ping (int val)
{
    // log the incoming value
    printf ("in Ping with value %d\n", val);
    // Make the call to Pong only if the decemented value has not gone negative
    if (--val >= 0)
        Pong(val);
    return val;
}

/****************************************************
 Function: Pong
 Summary:
 Pong is responsible for logging its received value (val) and conditionally calling Ping.
 After logging the received input, it passes the information to Ping with the input
 value decremented by 1 if the input was positive.

 When the function returns, it provides an int with the decremented value
 *****************************************************/
int Pong (int val)
{
    // log the incoming value
    printf ("in Pong with value %d\n", val);
    // Make the call to Ping only if the decemented value has not gone negative
    if (--val >= 0)
        Ping(val);
    return val;
}
