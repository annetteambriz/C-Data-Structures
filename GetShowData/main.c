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


/****************************************************
Function: getData
Summary:
GetData is a function that populates an array of EmployeeData structs.
It is passed the file name to open / read / close.

Parameters:
    filePath - file pointer to file containing employee data.
    employees - an array to populate employee data with.
    numEmployees - the maximum number of array entries to populate.

Returns:
    int - the number of elements placed into the employees array.

*****************************************************/

int getData(const char filepath[], EmployeeData employeeData[], const int numEmployees) {
    // attempt to open the file
    const FILE* employeeDataFile = fopen(filepath, "r");

    // exit if the file did not open
    if (employeeDataFile == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    // initialize a counter to track the number of employee records
    int count = 0;

    // while count is less than the numEmployees
    // read records from the file, storing each record in the employeeData array
    do {
        int numInput = fscanf(employeeDataFile, "%s%d%d",
                              &employeeData[count].name,
                              &employeeData[count].age,
                              &employeeData[count].salary);

        // ensure number of fields is as expected
        if (numInput != 3)
            break;

        // increment count of number of employees processed
        count++;
    } while(count < numEmployees); // prevent overflow of employee records in the array

    // we have stopped reading, so close the file and exit
    fclose (employeeDataFile);

    // return number of total employees add to the employeeData array
    return count;
}

/****************************************************
Function: showData
Summary:
showData is a function called to display the array contents on the console.
showData prints out the Name, Age and Salary fields for the requested number of items.

Parameters:
    employees - an array populated with employee data.
    numEmployees - the number of employees to print from the array.

Returns:
    void

*****************************************************/

void showData(EmployeeData employees[], const int numEmployees) {
    // print a simple head indicating the number of items that will be displayed
    printf("There are %d items in the employee data array\n", numEmployees);

    // loop through employees array and print out the employee details
    for (int i = 0; i < numEmployees; i++) {
        printf("%s %d %d\n", employees[i].name, employees[i].age, employees[i].salary);
    }
}

int main(void) {

    // declare variable to store number of employees to print
    int numEmployees;
    printf("Give me a number from 1 to 10: ");
    // store input from stdin to numEmployees
    scanf("%d", &numEmployees);

    // declare employee data array containing EmployeeData structs
    EmployeeData employeeData[numEmployees];

    // call getData to get employee data from a file
    // store number of entries stored in the array in total variable
    const int total = getData(DATA_FILEPATH, employeeData, numEmployees);

    // call showData to print data from getData
    showData(employeeData, total);

    return 0;
}