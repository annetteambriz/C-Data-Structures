#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

// The UserData struct defines what each node in the LL
// contains.
//

// User data in each node contains a priority and an associated time
typedef struct {
    int priority;
    char time[80];
} UserData, *UserDataPtr;



#endif // USERDATA_H_INCLUDED
