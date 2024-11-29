#include <stdio.h>
#include <string.h>


struct Employee {
    int employeeCode;
    char employeeName[50];
    int dateOfJoining; 
};

void initializeEmployees(struct Employee employees[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter details for employee %d:\n", i + 1);
        printf("Employee Code: ");
        scanf("%d", &employees[i].employeeCode);
        printf("Employee Name: ");
        scanf(" %[^\n]", employees[i].employeeName); // To handle spaces in name
        printf("Date of Joining (Year): ");
        scanf("%d", &employees[i].dateOfJoining);
    }
}

void displayEmployeesWithTenure(struct Employee employees[], int size, int currentYear) {
    int count = 0;
    printf("\nEmployees with more than 3 years of tenure:\n");
    for (int i = 0; i < size; i++) {
        int tenure = currentYear - employees[i].dateOfJoining;
        if (tenure > 3) {
            printf("Employee Code: %d, Name: %s, Tenure: %d years\n",
                   employees[i].employeeCode, employees[i].employeeName, tenure);
            count++;
        }
    }
    printf("Total employees with more than 3 years of tenure: %d\n", count);
}

int main() {
    struct Employee employees[4];
    int currentYear;

  
    initializeEmployees(employees, 4);

   
    printf("\nEnter the current year: ");
    scanf("%d", &currentYear);

    
    displayEmployeesWithTenure(employees, 4, currentYear);

    return 0;
}

