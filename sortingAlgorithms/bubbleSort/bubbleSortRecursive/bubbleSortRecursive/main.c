#include <stdio.h>

#define N 6

void bubbleSort(int arr[], int n);
int bubble(int arr[], int n);
void swap(int* a, int* b);

int main(int argc, const char * argv[]) {
    int arr[N] = { 45, 14, 61, 37, 56, 22 };
    
    bubbleSort(arr, N);
    
    for(int i=0; i<N; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
    return 0;
}


void bubbleSort(int arr[], int n) {
    int not_sorted = 1;
    
    while(n > 1 && not_sorted) {
        not_sorted = bubble(arr, n--);
    }
}

int bubble(int arr[], int n) {
    int swapped = 0;
    
    for(int i=1; i < n; i++) {
        if(arr[i-1] > arr[i]) {
            swap(&arr[i-1], &arr[i]);
            swapped = 1;
        }
    }
    
    return swapped;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
