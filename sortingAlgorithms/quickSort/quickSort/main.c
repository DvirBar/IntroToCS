#include <stdio.h>

void quick_sort(int a[], int n);
void swap(int* a, int* b);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

void quick_sort(int a[], int n) {
    int pivot, bottom = 1, top = n - 1;
    
    if(n < 2)
        return;
    
    swap(&a[0], &a[n/2]);
    pivot = a[0];
    
    while(bottom <= top) {
        while(top >= bottom && a[top] >= pivot)
            top--;
        while (bottom <= top && a[bottom] < pivot)
            bottom++;
        if(bottom < top)
            swap(&a[bottom++], &a[top--]);
    }
    
    swap(&a[0], &a[top]);
    
    quick_sort(a, top);
    quick_sort(a + top + 1, n - top - 1);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}



