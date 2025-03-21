#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

/****************************************************
The UserData struct defines what each node in the LL contains.
A structure to hold User Data.
Contains an integer representing importance.
Contains an array of characters containing a task name.
*****************************************************/

typedef struct
{
    int importance;
    char taskName[80];
} UserData, *UserDataPtr;


#endif // USERDATA_H_INCLUDED
