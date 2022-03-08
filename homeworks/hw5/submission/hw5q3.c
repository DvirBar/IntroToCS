#include <stdio.h>
#include <stdbool.h>

#define N 5
#define ASSIGNED_EMPLOYEE -1
#define UNASSIGNED_EMPLOYEE 1

void read_matrix(int arr[N][N]);
bool is_assigned_employee(int arr[N][N], int employee, int task);
int find_possible_assignments(int arr[N][N], int task);
void print_possible_assignments(int num_possible_assignments);


int main() {
    int arr[N][N] = {{0}}, num_possible_assingments = 0;
    read_matrix(arr);
    
    num_possible_assingments = find_possible_assignments(arr, 0);
    
    print_possible_assignments(num_possible_assingments);
        
    return 0;
}

// Reads matrtix from user input
void read_matrix(int arr[N][N]) {
    printf("Enter the matrix:\n");
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

// Recursive function to find all possible assignments starting from a given task
int find_possible_assignments(int arr[N][N], int task) {
    int counter = 0;
    
    for(int i = 0; i < N; i++) {
        if(arr[i][task] == 0 || is_assigned_employee(arr, i, task)) {
            continue;
        }
        
        if(task == N-1) {
            counter++;
        }
        
        else {
            arr[i][task] = ASSIGNED_EMPLOYEE;
            counter += find_possible_assignments(arr, task+1);
            arr[i][task] = UNASSIGNED_EMPLOYEE;
        }
    }

    return counter;
}

// Checks if a user has already been assigned with a task
bool is_assigned_employee(int arr[N][N], int employee, int task) {
    for(int j = task-1; j >= 0; j--) {
        if(arr[employee][j] == ASSIGNED_EMPLOYEE) {
            return true;
        }
    }
    
    return false;
}

// Prints how many possible assignments get be made
void print_possible_assignments(int num_possible_assignments) {
    printf("The result is %d", num_possible_assignments);
}
