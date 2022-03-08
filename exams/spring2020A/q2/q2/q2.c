#include <stdio.h>

#define N 8

int FindFixedPoint(int a[], int n);

int main() {
    int a[N] = {-30, 1, 5, 8, 12, 32, 40, 80};
    
    printf("%d\n", FindFixedPoint(a, N));
}

int FindFixedPoint(int a[], int n) {
    int left = 0, right = n-1, mid = (left+right)/2;
    
    while(left <= right) {
        if(a[mid] == mid)
            return mid;
        
        if(a[mid] > mid)
            right = mid-1;
        
        if(a[mid] < mid)
            left = mid+1;
        mid = (left+right)/2;
    }
    
    return -1;
}
