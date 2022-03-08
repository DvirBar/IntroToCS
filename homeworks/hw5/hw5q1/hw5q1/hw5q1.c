#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TWO 2
#define UNDEFINED_VALUE -1

int read_array_size(int* n);
void read_array(int arr[], int n);
void merge_sort(int a[], int n);
void internal_msort(int a[], int n, int helper_array[]);
void merge(int a[], int na, int b[], int nb, int c[]);
int find_recommended(int arr[], int n);
void print_recommended(int recommended);


int main() {
    int n = 0, recommended = 0;
    if(!read_array_size(&n)) {
        return 0;
    }
    
    int* arr = malloc(sizeof(int) * n);
    
    if(arr == NULL) {
        return 0;
    }
    
    read_array(arr, n);
    merge_sort(arr, n);
    recommended = find_recommended(arr, n);
    print_recommended(recommended);
    free(arr);
    return 0;
}

/* Get array size from user input.
   Returns true if input is correctly typed and false otherwise */
int read_array_size(int* n) {
    printf("Enter the length of the array:\n");
    return scanf("%d", n) == 1;
}

// Get array from user input
void read_array(int arr[], int n) {
    printf("Enter the array:\n");
        
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
}

// Merge sort algorithm
void merge_sort(int a[], int n) {
    int* tmp_arr = malloc(sizeof(int) * n);
    internal_msort(a, n, tmp_arr);
    free(tmp_arr);
}

// Recursive function to perform merge sort
void internal_msort(int a[], int n, int helper_arr[]) {
    int left = n/TWO, right = n - left;
    
    if (n < TWO) {
        return;
    }
    
    internal_msort(a, left, helper_arr);
    internal_msort(a+left, right, helper_arr);
    merge(a, left, a+left, right, helper_arr);
    memcpy(a, helper_arr, n * sizeof(int));
}

// Merge of array cells
void merge(int a[], int na, int b[], int nb, int c[]) {
    int ia, ib, ic;
    
    for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++) {
        if(a[ia] < b[ib]) {
            c[ic] = a[ia];
            ia++;
        }
        else {
            c[ic] = b[ib];
            ib++;
        }
    }
    
    for(;ia < na; ia++, ic++) c[ic] = a[ia];
    for(;ib < nb; ib++, ic++) c[ic] = b[ib];
}

/* Finds and returns a recommended number in a sorted array.
   If not found, the function returns -1. */
int find_recommended(int sorted_arr[], int n) {
    int counter = 0;
    
    for(int i = n-1; i >= 0; i--) {
        if(counter < sorted_arr[i]) {
            counter++;
        }
        
        else if(i < n-1 && counter != sorted_arr[i]) {
            return counter;
        }
        
        else {
            return UNDEFINED_VALUE;
        }
    }
    
    return counter;
}

// Prints if a number is recommended
void print_recommended(int recommended) {
    if(recommended == UNDEFINED_VALUE) {
        printf("The array is not recommended");
    }
    
    else {
        printf("The array is recommended and x = %d", recommended);
    }
}
