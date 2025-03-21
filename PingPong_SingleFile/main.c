#include <stdio.h>

// Here is a simple program called PingPong. It is designed to
// demonstrate why you should (and in this case MUST) declare functions
// before you write their code (called defining a function). The program
// will simply call Ping from the main() with a number. Ping will
// call Pong with the decremented number if the input is positive. Pong behaves the
// same
// way, calling Ping with a decremented number. The functions will stop calling
// each other if the value they receive is negative.
// The C compiler is a single pass system that either
// assumes a function return type is int or builds a
// function declaration from the function definition, whichever
// comes first in a compilation. That can be a problem whenever you call a function
// that needs arguments or has a return type other than int. Why? Because the implied
// return type will be incorrect and the caller will not receive the returned information
// as the correct type.
// Declarations of Ping and Pong follow, so that the compiler knows that each of them
// receive a float and return a float.
// Without these statements, you cannot reorder this code successfully
// to get a good compilation. With them, your function definitions can be in any order
// Technically, you could do without the Ping declaration, but only
// because it is seen by the compiler before a call to it has been seen.
// If the definition for Pong came first, you could do without the Pong
// declaration for the same reason, but you would then need the Ping
// declaration.
// Bottom line: declare them all so you don't have to worry about order
// // That is why C has "include" statements that does precisely that!
// See what happens if you comment out the include for stdio.h!
float Ping(float val);
float Pong(float val);
// defines are a very convenient way to give a value a name and then use the
// name everywhere in place of the value. That means that if you have to change
// the value to something else, you only need to change it in one spot!
// Notice the syntax is <name> <value> with NO <semicolon> at the end of the line.
#define startTestValue 1.5f
#define decrementValue .25f
// Here is Ping. Play with it, changing only the parameter "val" type
// from float to int. You will see the compiler generates an error
// called "conflicting type", since it has been told Ping expects a float.
// Also, try changing the return type from float to int in the Ping definition
// below. You will see the same error.
//
// Bottom line... to ensure that you can enforce consistency on function parameters
// and return types, all functions need to be declared prior to their definition


// Function Ping
// Inputs: a float named val
// Processing: After logging the received input, call Pong with the input
// value decremented by "decrementValue" if the input was positive.
// Output: the value from Pong or the input value if it was negative
float Ping(float val) {
    // log the entry value
    printf ("Ping entered with val = %f..\n", val);
    // As long as the number is positive, call Pong with the
    // number decremented by decrementValue.
    if (val >= 0.0) {
        printf ("\tCalling Pong with val %f\n", val - decrementValue);
        val = Pong(val - decrementValue);
    }
    return val;
    // return the value returned from Pong or the input value if it is negative
}

// Function Pong
// Inputs: a float named val
// Processing: After logging the received input, call Ping with the input
// value decremented by "decrementValue" if the input was positive.
// Output: the value from Ping or the input value if it was negative
float Pong(float val) {
    // log the entry value
    printf ("Pong entered with val = %f..\n", val);
    // As long as the number is positive, call Ping with the
    // number decremented by decrementValue.
    if (val >= 0.0) {
        printf ("\tCalling Ping with val %f\n", val - decrementValue);
        val = Ping(val - decrementValue);
    }
    return val;
    // return the value returned from Ping or the input value if it is negative
}

// Function main
// Inputs: None
// Processing: Kick off a PingPong with a float that will be bounced
// between Ping and Pong until it is negative
// Output: 0 (function succeeded)
int main() {
    printf ("Calling for a PingPong with a value of %f\n", startTestValue);
    float finalValue = Ping(startTestValue);
    printf ("After PingPong processing, the value returned is %f\n", finalValue);
        return 0;
}
