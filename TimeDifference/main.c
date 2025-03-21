#include <stdio.h>

// Define number of minutes in a day constant
#define MINS_DAY 1440

/****************************************************
This structure type represents the hours and minutes of Time.
Time will be in a 24-hour format, rather than AM and PM
*****************************************************/

typedef struct {
    int hours;
    int minutes;
} Time;


/****************************************************
Function: TimeDifference
Summary:
TimeDifference is a function that receives a start time and end time that are structs.
It computes the difference in minutes between the start time and end time,
returning the number of minutes. If the end time is less than the start time we take that
to mean we have rolled over by a single day and will accommodate the time rollover.
*****************************************************/

/****************************************************
Function: TimeDifference
Summary:
    TimeDifference is a function that receives a start time and end time that are structs.
    It computes the difference in minutes between the start time and end time,
    returning the number of minutes. If the end time is less than the start time we take that
    to mean we have rolled over by a single day and will accommodate the time rollover.

Parameters:
    startTime - Time struct representing the start time
    endTime - Time struct representing the end time

Returns:
    int - value representing the difference in start/end time
    minutes.
*****************************************************/

int TimeDifference(Time startTime, Time endTime) {

    //calculate total minutes for startTime and endTime
    int totalStartTimeMinutes = (startTime.hours * 60) + startTime.minutes;
    int totalEndTimeMinutes = (endTime.hours * 60) + endTime.minutes;

    // calculate difference in startTime and endTime
    int difference = totalEndTimeMinutes - totalStartTimeMinutes;

    // if difference is negative, roll over a day and add the total minutes in a day
    // to the difference
    if (difference < 0) {
        difference = MINS_DAY + difference;
    }
    return difference;
}

int main(void) {
    Time startTime = {.hours = 11, .minutes = 52};
    Time endTime = {.hours = 14, .minutes = 43};

    printf("The startTime is %d hours and %d minutes.\n", startTime.hours, startTime.minutes);
    printf("The endTime is %d hours and %d minutes.\n", endTime.hours, endTime.minutes);
    printf("Time difference from start and end time is: %d minutes\n", TimeDifference(startTime, endTime));
    printf("Time difference from end and start time is: %d minutes\n", TimeDifference(endTime, startTime));

    return 0;
}
