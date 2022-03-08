#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int read_array_size(int* n);
void read_array(char* arr);
bool is_palindrome(char* arr, int left, int right);
void print_palindrome_msg(bool is_palindrome);

int main() {
    int n = 0;
    
    if(!read_array_size(&n)) {
        return 0;
    }
    
    if(n == 0) {
        print_palindrome_msg(true);
        return 0;
    }
    
    char* arr = malloc(sizeof(char) * n);
    
    if(arr == NULL) {
        return 0;
    }
    
    read_array(arr);
    print_palindrome_msg(is_palindrome(arr, 0, n-1));
    
    free(arr);
    return 0;
}

// Gets array size from user input
int read_array_size(int* n) {
    printf("Enter the length of the array:\n");
    return scanf("%d", n) == 1;
}

// Gets array from user input
void read_array(char* arr) {
    printf("Enter the array:\n");
    scanf(" %s", arr);
}

// Recursive function to check if a text is a polindrome
bool is_palindrome(char* arr, int left, int right) {
    if(left+1 >= right-1) {
        return arr[left] == arr[right];
    }
    
    return is_palindrome(arr, left+1, right-1)*(arr[left] == arr[right]);
}

// Prints if a the text is a palindrome or not
void print_palindrome_msg(bool is_palindrome) {
    if(is_palindrome) {
        printf("A palindrome");
    }
    
    else {
        printf("Not a palindrome");
    }
}


