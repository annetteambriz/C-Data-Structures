#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

// The UserData struct defines what each node in the LL
// contains.
//

// User data in each node contains an integer and an array of chars
typedef struct
{
    int taskNumber;
} UserData, *UserDataPtr;


#endif // USERDATA_H_INCLUDED
