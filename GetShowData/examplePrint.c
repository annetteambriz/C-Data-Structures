#include <stdio.h>
#include <stdlib.h>

// define file path constant
#define DATA_FILEPATH "/Users/annette/Repositories/C/CLionProjects/C_Data_Structures/GetShowData/Problem1_2DataFile.txt"

/****************************************************
This structure type represents the name, age and salary
for an employee.
Name is an array of chars, age and salary integers.
*****************************************************/

typedef struct {
    char name[30];
    int age;
    int salary;
} EmployeeData;

int main(void) {
    printf("Hello, World!\n");
    EmployeeData myData;
    // attempt to open the file
    FILE *inputFile = fopen(DATA_FILEPATH, "r");

    // exit if the file did not open
    if (inputFile == NULL)
    {
        printf ("File did not open! Exiting program\n");
        exit(0);
    }

    // read records from the file, printing out each record
    int count;
    do {
        // try to read in a record
        count = fscanf (inputFile, "%s%d%d", myData.name, &myData.age, &myData.salary);
        // we expected to read in 3 things, so count should return as 3
        if (count == 3)
            printf ("Name was %s, age was %d, salary was %d\n", myData.name, myData.age, myData.salary);
        // loop to try to read in another record
    } while (count == 3);

    // we have stopped reading, so close the file and exit
    fclose (inputFile);
    return 0;
}