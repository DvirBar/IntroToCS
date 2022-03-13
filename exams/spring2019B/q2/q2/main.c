#include <stdio.h>

#define N 12

void CycleShift(int arr[], int n, int k);

int main() {
    int arr[N] = {8, -2, 5, 5, 3, 6, 13, 1, 21, 0, 7, -1};
    
    CycleShift(arr, N, 4);
    
    for(int i=0; i<N; i++) {
        printf("%d", arr[i]);
        
        if(i != N-1)
            printf(", ");
    }
    
    printf("\n");
    
    return 0;
}

void CycleShift(int arr[], int n, int k) {
    int lastVal = 0, temp = 0;
    for(int i=0; i<k; i++) {
        lastVal = arr[i];
        for(int j=0; j<n; j+=k) {
            temp = arr[(i+j+k)%n];
            arr[(i+j+k)%n] = lastVal;
            lastVal = temp;
        }
    }
}
