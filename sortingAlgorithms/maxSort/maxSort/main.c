
#include <stdio.h>

int index_of_max(int a[], int n);
void max_sort(int a[], int n);
void swap(int* a, int* b);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

void max_sort(int a[], int n) {
    int i_max = 0;
    
    for(int length = n; length > 1; length--) {
        i_max = index_of_max(a, n);
        swap(&a[i_max], &a[length-1]);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int index_of_max(int a[], int n) {
    int i_max = 0;
    
    for(int i=0; i < n; i++) {
        if(a[i] > i_max)
            i_max = a[i];
    }
    
    return i_max;
}
